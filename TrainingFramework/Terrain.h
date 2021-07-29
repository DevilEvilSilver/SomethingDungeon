#pragma once
#include <vector>
#include "Object.h"


class Terrain: public Object {
public:
	std::vector<unsigned int> m_iTextureID;
	GLfloat m_fTextureScale;

	Terrain();
	Terrain(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		unsigned int type, float posX, float posY, float width, float height, float radius,
		std::vector<unsigned int> textureID, GLfloat textureScale);
	~Terrain();

	void Update(float frameTime);
	void Render(Camera *camera);
};