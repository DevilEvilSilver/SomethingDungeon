#pragma once
#include <vector>
#include "Terrain.h"
#include "SpriteObject.h"

class Renderer {
private:
	static Renderer* s_Instance;

public:
	Renderer();
	~Renderer();

	void Init();
	void DrawTexture2D(Object *object, Camera *camera);
	void DrawTerrain(Terrain *object, Camera *camera);
	void DrawSprite(SpriteObject *object, Camera *camera);

	static Renderer* GetInstance();
	static void ResetInstance();
};