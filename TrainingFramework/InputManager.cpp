#include "stdafx.h"
#include "InputManager.h"
#include "define.h"
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

InputManager* InputManager::s_Instance = NULL;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update(unsigned char key, bool bIsPressed)
{
	switch (key) {
	case 'W':
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_W;
		else
			keyPressed = keyPressed ^ KEY_W;
		break;
	case 'A':
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_A;
		else
			keyPressed = keyPressed ^ KEY_A;
		break;
	case 'S':
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_S;
		else
			keyPressed = keyPressed ^ KEY_S;
		break;
	case 'D':
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_D;
		else
			keyPressed = keyPressed ^ KEY_D;
		break;
	
	case VK_UP:
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_UP;
		else
			keyPressed = keyPressed ^ KEY_UP;
		break;
	
	}
	printf("keyPressed: %d\n", keyPressed);
}

InputManager* InputManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new InputManager();
	return s_Instance;
}

void InputManager::ResetInstance()
{
	delete s_Instance;
	s_Instance = NULL;
}
