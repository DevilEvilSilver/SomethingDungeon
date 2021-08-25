// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "define.h"
#include "Vertex.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "SoundEngine.h"
#include "StatePlay.h"
#include "InputManager.h"
#include "StateManager.h"

Text *FPSCountText;
float fDeltaTime = 0.0f;
unsigned int frames = 0;

int Init(ESContext* esContext) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ResourceManager::GetInstance();
	SoundEngine::GetInstance();
	Renderer::GetInstance();
	InputManager::GetInstance();
	StateManager::GetInstance();

	FPSCountText = new Text("0", SHADER_TEXT, FONT_FUTURE, TEXT_COLOR::GREEN, 0.0f, 20.0f, 1.0f);
	
	return 0;
}

void Draw(ESContext* esContext)
{
	//fps
	std::clock_t start;
	start = std::clock();

	//clear + render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	StateManager::GetInstance()->Render();

	Renderer::GetInstance()->DrawText2(FPSCountText);

	//fps
	DWORD frameTime = std::clock() - start;
	fDeltaTime += frameTime;
	frames++;
	if (fDeltaTime > 1000.0f) {
		FPSCountText->setText(std::to_string(frames));
		frames = 0;
		fDeltaTime -= 1000.0f;
	}

	if (frameTime < 1000.0f / LIMIT_FPS) {
		fDeltaTime += 1000.0f / LIMIT_FPS - frameTime;
		Sleep(1000.0f / LIMIT_FPS - frameTime);
	}

	//display
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

}

void Update(ESContext* esContext, float deltaTime)
{
	StateManager::GetInstance()->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	InputManager::GetInstance()->Key(key, bIsPressed);
}

void TouchActionLeftDown(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseLeft(true, x, y);
	InputManager::GetInstance()->MouseMove(x, y);
}

void TouchActionLeftUp(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseLeft(false, x, y);
	InputManager::GetInstance()->MouseMove(x, y);
}

void TouchActionRightDown(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseRight(true, x, y);
	InputManager::GetInstance()->MouseMove(x, y);
}

void TouchActionRightUp(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseRight(false, x, y);
	InputManager::GetInstance()->MouseMove(x, y);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{	
	InputManager::GetInstance()->MouseMove(x, y);		
}

void TouchActionHover(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseMove(x, y);
}

void CleanUp()
{
	StateManager::GetInstance()->ResetInstance();
	InputManager::GetInstance()->ResetInstance();
	SoundEngine::GetInstance()->ResetInstance();
	Renderer::GetInstance()->ResetInstance();
	ResourceManager::GetInstance()->ResetInstance();

	delete FPSCountText;
}

void memoryDumpLeak() {
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

}

int _tmain(int argc, _TCHAR* argv[])
{
	
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "CrossDungeon", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0) return 0;

	//draw
	esRegisterDrawFunc(&esContext, Draw);
	
	//update
	esRegisterUpdateFunc(&esContext, Update);
	
	//key handle
	esRegisterKeyFunc(&esContext, Key);
	
	//mouse handle
	esRegisterMouseLeftDownFunc(&esContext, TouchActionLeftDown);
	esRegisterMouseRightDownFunc(&esContext, TouchActionRightDown);
	esRegisterMouseLeftUpFunc(&esContext, TouchActionLeftUp);
	esRegisterMouseRightUpFunc(&esContext, TouchActionRightUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esRegisterMouseHoverFunc(&esContext, TouchActionHover);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	memoryDumpLeak();

	printf("Press any key...\n");
	_getch();

	return 0;
}

