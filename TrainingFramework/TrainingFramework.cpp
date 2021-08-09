// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "define.h"
#include "Vertex.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <conio.h>


#include "InputManager.h"
#include "StateManager.h"
#include "PhysicEngine.h"

#include "SoundEngine.h"



int Init(ESContext* esContext) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ResourceManager::GetInstance();
	Renderer::GetInstance();
	PhysicEngine::GetInstance();
	InputManager::GetInstance();
	StateManager::GetInstance();
	SoundEngine::GetInstance();
	return 0;
}

void Draw(ESContext* esContext)
{
	//fps
	DWORD start, end;
	start = GetTickCount();

	//clear + render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	StateManager::GetInstance()->Render();

	//fps
	end = GetTickCount();
	DWORD frameTime = end - start;
	if (frameTime < 1000.0f/ LIMIT_FPS)
		Sleep(1000.0f / LIMIT_FPS - frameTime);

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
	InputManager::GetInstance()->MouseMove(x, y);
	InputManager::GetInstance()->MouseLeft(true);
}

void TouchActionLeftUp(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseLeft(false);
}

void TouchActionRightDown(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseMove(x, y);
	InputManager::GetInstance()->MouseRight(true);
}

void TouchActionRightUp(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseRight(false);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{	
	InputManager::GetInstance()->MouseMove(x, y);		
}

void CleanUp()
{
	ResourceManager::GetInstance()->ResetInstance();
	Renderer::GetInstance()->ResetInstance();
	PhysicEngine::GetInstance()->ResetInstance();
	InputManager::GetInstance()->ResetInstance();
	StateManager::GetInstance()->ResetInstance();
	
	SoundEngine::GetInstance()->ResetInstance();
}

void CrtMemoryDump() 
{
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
	esCreateWindow(&esContext, "EmojiDungeon", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	
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

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	CrtMemoryDump();
	
	
	printf("Press any key...\n");
	_getch();

	return 0;
}

