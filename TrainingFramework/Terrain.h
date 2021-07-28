#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Object.h"
#include "Camera.h"

class Terrain: public Object {
public:
	GLfloat m_fTextureScale;

	Terrain();
	Terrain(unsigned int modelID, unsigned int shaderID, Matrix worldMatrix, GLfloat textureScale); 
	~Terrain();

	void Update(float frameTime);
	void Render(Camera *camera);
};