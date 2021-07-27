#pragma once
#include <vector>
#include "Terrain.h"

class Renderer {
private:
	static Renderer* s_Instance;

public:
	Renderer();
	~Renderer();

	void Init();
	void DrawTexture2D(Object *object, Camera *camera);
	void DrawTerrain(Terrain *object, Camera *camera);
	void DrawTextureCube(Object *object, Camera *camera);

	static Renderer* GetInstance();
	static void ResetInstance();
};