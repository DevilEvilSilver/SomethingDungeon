#pragma once
#include <vector>
#include "StaticObject.h"
#include "AnimatedObject.h"

class Renderer {
private:
	static Renderer* s_Instance;

public:
	Renderer();
	~Renderer();

	void Init();
	void DrawStatic(StaticObject *object, Camera *camera);
	void DrawAnimated(AnimatedObject *object, Camera *camera);

	static Renderer* GetInstance();
	static void ResetInstance();
};