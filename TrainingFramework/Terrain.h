#pragma once
#include <vector>
#include "Object.h"


class Terrain: public Object {
public:
	unsigned int m_iModelID;
	std::vector<unsigned int> m_iTextureID;
	GLfloat m_fTextureScale;

	Terrain();
	Terrain(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		std::vector<unsigned int> textureID, GLfloat textureScale);
	~Terrain();

	void Update(float frameTime);
	void Render(Camera *camera);
};