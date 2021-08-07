#pragma once
#include <vector>
class InputManager {
private:
	static InputManager* s_Instance;
public:

	int keyPressed = 0;
	InputManager();
	~InputManager();

	void Key(unsigned char key, bool bIsPressed);




	static InputManager* GetInstance();
	static void ResetInstance();
};

