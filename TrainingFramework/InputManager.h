#pragma once
#include <vector>
class InputManager {
private:
	static InputManager* s_Instance;



public:

	int keyPressed=0;
	const int KEY_W = 1 << 0;
	const int KEY_A = 1 << 1;
	const int KEY_S = 1 << 2;
	const int KEY_D = 1 << 3;
	const int KEY_UP = 1 << 4;

	InputManager();
	~InputManager();

	void Update(unsigned char key, bool bIsPressed);




	static InputManager* GetInstance();
	static void ResetInstance();
};

