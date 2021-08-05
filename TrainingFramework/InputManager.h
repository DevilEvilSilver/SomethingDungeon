#pragma once
#include <vector>
#include "Camera.h"
class InputManager {
private:
	static InputManager* s_Instance;



public:

	int keyPressed = 0;

	int mouseX = 0;
	int mouseY = 0;
	

	InputManager();
	~InputManager();

	void Key(unsigned char key, bool bIsPressed);

	void MouseLeft(bool bIsPressed);
	void MouseRight(bool bIsPressed);
	void MouseMove(int x,int y);					////chi moi luu lai vi tri tren man hinh chu chua phai vi tri trong khong gian

	Vector2 MousePosition(Camera* stateCamera);		//tra ve vij tri trong khong gian voi camera hien tai

	static InputManager* GetInstance();
	static void ResetInstance();
};

