#pragma once
#include <vector>
#include <string>
#include "Model.h"
#include "Object.h"

class AnimatedObject : public Object {
public:
	std::string m_strState;			//Animation ID
	unsigned int m_iCurrFrameIndex;
	float m_fCurrFrameTime;

	AnimatedObject();
	AnimatedObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		unsigned int type, float posX, float posY, float width, float height, float radius);
	~AnimatedObject();

	void Update(float frameTime);
	void Render(Camera *camera);
};
