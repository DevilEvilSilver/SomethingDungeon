#pragma once
#include <vector>
#include "Terrain.h"
#include "AnimatedObject.h"

class Renderer {
private:
	static Renderer* s_Instance;

public:
	Renderer();
	~Renderer();

	void Init();
	void DrawTerrain(Terrain *object, Camera *camera);
	void DrawSprite(AnimatedObject *object, Camera *camera);

	static Renderer* GetInstance();
	static void ResetInstance();
};