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
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	//SceneManager::GetInstance()->CheckTouchPosition(x, y);
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	//SceneManager::GetInstance()->SetAllNotHold(x, y);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
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
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
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

