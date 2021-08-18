#pragma once
#include <vector>
#include "Camera.h"
#include "Singleton.h"

class InputManager:public Singleton<InputManager>
{

public:

	int keyPressed = 0;

	int mouseLX = 0; //Left down/up
	int mouseLY = 0;
	int mouseRX = 0; //Right down/up
	int mouseRY = 0;
	int mouseX = 0; //Move
	int mouseY = 0;
	

	InputManager();
	~InputManager();

	void Key(unsigned char key, bool bIsPressed);

	void MouseLeft(bool bIsPressed, int x, int y);
	void MouseRight(bool bIsPressed, int x, int y);
	void MouseMove(int x,int y);					////chi moi luu lai vi tri tren man hinh chu chua phai vi tri trong khong gian

	void ResetInput();

	Vector2 GetMousePosition(Camera* stateCamera, int x, int y);		//tra ve vij tri trong khong gian voi camera hien tai


};

