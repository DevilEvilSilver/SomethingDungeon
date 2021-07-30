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

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
		
	ResourceManager::GetInstance();
	SceneManager::GetInstance();

	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::GetInstance()->Render();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	SceneManager::GetInstance()->Update(deltaTime);
}

void TouchActionDown(ESContext *esContext, int x, int y)
{
	//SceneManager::GetInstance()->CheckTouchPosition(x, y);
}

void TouchActionUp(ESContext *esContext, int x, int y)
{
	//SceneManager::GetInstance()->SetAllNotHold(x, y);
}

void TouchActionMove(ESContext *esContext, int x, int y)
{
	//SceneManager::GetInstance()->TouchMove(x, y);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 'W':
	case 'w':
		SceneManager::GetInstance()->m_Camera->m_isMoveForward = bIsPressed;
		break;
	case 'S':
	case 's':
		SceneManager::GetInstance()->m_Camera->m_isMoveBackward = bIsPressed;
		break;
	case 'A':
	case 'a':
		SceneManager::GetInstance()->m_Camera->m_isMoveLeft = bIsPressed;
		break;
	case 'D':
	case 'd':
		SceneManager::GetInstance()->m_Camera->m_isMoveRight = bIsPressed;
		break;
	case VK_UP:
		SceneManager::GetInstance()->m_Camera->m_isRotUp = bIsPressed;
		break;
	case VK_DOWN:
		SceneManager::GetInstance()->m_Camera->m_isRotDown = bIsPressed;
		break;
	case VK_LEFT:
		SceneManager::GetInstance()->m_Camera->m_isRotLeft = bIsPressed;
		break;
	case VK_RIGHT:
		SceneManager::GetInstance()->m_Camera->m_isRotRight = bIsPressed;
		break;
	}
}

void CleanUp()
{
	SceneManager::GetInstance()->ResetInstance();
	ResourceManager::GetInstance()->ResetInstance();
	Renderer::GetInstance()->ResetInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

