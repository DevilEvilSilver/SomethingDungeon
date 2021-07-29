#pragma once
#include <vector>
#include <string>
#include "Model.h"
#include "Object.h"

class SpriteObject : public Object {
public:
	std::string m_strState;
	unsigned int m_iCurrFrameIndex;
	float m_fCurrFrameTime;

	SpriteObject();
	SpriteObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		unsigned int type, float posX, float posY, float width, float height, float radius);
	~SpriteObject();

	void Update(float frameTime);
	void Render(Camera *camera);
};
