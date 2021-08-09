#pragma once
#include <vector>
#include "Object.h"
#include"Text.h"

class Renderer {
private:
	static Renderer* s_Instance;

public:
	Renderer();
	~Renderer();

	void Init();
	void DrawAnimated(Object *object, Camera *camera);
	void DrawText2(Text* text);
	//void DrawText(Text* text);

	static Renderer* GetInstance();
	static void ResetInstance();
};