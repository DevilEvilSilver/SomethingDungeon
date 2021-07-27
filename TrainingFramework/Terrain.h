#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Object.h"
#include "Camera.h"

class Terrain: public Object {
public:
	float m_fFogStart;
	float m_fFogLength;
	Vector3 m_FogColor;

	Terrain();
	Terrain(unsigned int modelID, unsigned int shaderID, Matrix worldMatrix, float fogStart, float fogLength, Vector3 fogColor); 
	~Terrain();

	void Update(float frameTime);
	void Render(Camera *camera);
};