#include "stdafx.h"
#include "InputManager.h"
#include "define.h"
#include <Windows.h>
#include <WinUser.h>
#define _CRT_SECURE_NO_WARNINGS



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

void InputManager::MouseLeft(bool bIsPressed, int x, int y)
{
	if (bIsPressed == true)
		keyPressed = keyPressed | MOUSE_LEFT;
	else
		keyPressed = keyPressed ^ MOUSE_LEFT;

	mouseLX = x;
	mouseLY = y;
}

void InputManager::MouseRight(bool bIsPressed, int x, int y)
{
	if (bIsPressed == true)
		keyPressed = keyPressed | MOUSE_RIGHT;
	else
		keyPressed = keyPressed ^ MOUSE_RIGHT;

	mouseRX = x;
	mouseRY = y;
}

void InputManager::MouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void InputManager::ResetInput() {
	keyPressed = 0;
	mouseLX = 0; 
	mouseLY = 0;
	mouseRX = 0; 
	mouseRY = 0;
	mouseX = 0;
	mouseY = 0;
}

Vector2 InputManager::GetMousePosition(Camera* stateCamera, int x, int y)
{
	Vector2 camScale = stateCamera->GetViewScale();
	float posX = x / SCREEN_W * camScale.x + stateCamera->GetPosition().x - camScale.x/2;
	float posY = y / SCREEN_H * camScale.y * -1 + stateCamera->GetPosition().y + camScale.y/2;

	

	return Vector2(posX, posY);
}

