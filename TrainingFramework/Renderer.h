#pragma once
#include <vector>
#include "Object.h"

class Renderer {
private:
	static Renderer* s_Instance;

public:
	Renderer();
	~Renderer();

	void Init();
	void DrawAnimated(Object *object, Camera *camera);

	static Renderer* GetInstance();
	static void ResetInstance();
};