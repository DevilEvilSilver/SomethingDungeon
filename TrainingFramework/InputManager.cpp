#include "stdafx.h"
#include "InputManager.h"
#include "define.h"
#include <Windows.h>
#include <WinUser.h>
#define _CRT_SECURE_NO_WARNINGS

InputManager* InputManager::s_Instance = NULL;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Key(unsigned char key, bool bIsPressed)
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
	case VK_DOWN:
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_DOWN;
		else
			keyPressed = keyPressed ^ KEY_DOWN;
		break;
	case VK_LEFT:
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_LEFT;
		else
			keyPressed = keyPressed ^ KEY_LEFT;
		break;
	case VK_RIGHT:
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_RIGHT;
		else
			keyPressed = keyPressed ^ KEY_RIGHT;
		break;
	case ' ':
		if (bIsPressed == true)
			keyPressed = keyPressed | KEY_SPACE;
		else
			keyPressed = keyPressed ^ KEY_SPACE;
		break;
	}
	
	//printf("keyPressed: %d\n", keyPressed);
}

void InputManager::MouseLeft(bool bIsPressed)
{
	if (bIsPressed == true)
		keyPressed = keyPressed | MOUSE_LEFT;
	else
		keyPressed = keyPressed ^ MOUSE_LEFT;
}

void InputManager::MouseRight(bool bIsPressed)
{
	if (bIsPressed == true)
		keyPressed = keyPressed | MOUSE_RIGHT;
	else
		keyPressed = keyPressed ^ MOUSE_RIGHT;
}

void InputManager::MouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

Vector2 InputManager::MousePosition(Camera* stateCamera)
{
	Vector2 camScale = stateCamera->GetViewScale();
	float x = mouseX / SCREEN_W * camScale.x + stateCamera->GetPosition().x - 10.0f;
	float y = mouseY / SCREEN_H * camScale.y * -1 + stateCamera->GetPosition().y + 10.0f;

	

	return Vector2(x,y);
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