// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "define.h"
#include "Vertex.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <conio.h>

//Son
#include "InputManager.h"
#include "StateManager.h"



void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	StateManager::GetInstance()->Render();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	StateManager::GetInstance()->Update(deltaTime);

	//printf("key: %d\n",InputManager::GetInstance()->keyPressed);
}

void TouchActionRightDown(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseMove(x, y);
	InputManager::GetInstance()->MouseRight(true);
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

void TouchActionRightUp(ESContext* esContext, int x, int y)
{
	InputManager::GetInstance()->MouseRight(false);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	//printf("Move %d %d\n", x, y);
	
	InputManager::GetInstance()->MouseMove(x, y);		
	//SceneManager::GetInstance()->TouchMove(x, y);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	InputManager::GetInstance()->Key(key, bIsPressed);

}

void CleanUp()
{
	ResourceManager::GetInstance()->ResetInstance();
	Renderer::GetInstance()->ResetInstance();

	InputManager::GetInstance()->ResetInstance();
	StateManager::GetInstance()->ResetInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esRegisterMouseLeftDownFunc(&esContext, TouchActionLeftDown);
	esRegisterMouseRightDownFunc(&esContext, TouchActionRightDown);
	
	esRegisterMouseLeftUpFunc(&esContext, TouchActionLeftUp);
	esRegisterMouseRightUpFunc(&esContext, TouchActionRightUp);

	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	//MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

