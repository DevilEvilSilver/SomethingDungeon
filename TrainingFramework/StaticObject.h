#pragma once
#include <vector>
#include "Object.h"


class StaticObject: public Object {
public:
	std::vector<unsigned int> m_iTextureID;
	GLfloat m_fTextureScale;

	StaticObject();
	StaticObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		unsigned int type, float posX, float posY, float width, float height, float radius,
		std::vector<unsigned int> textureID, GLfloat textureScale);
	~StaticObject();

	void Update(float frameTime);
	void Render(Camera *camera);
};