#pragma once
#include <vector>
#include <string>
#include "Model.h"
#include "Object.h"

class SpriteObject : public Object {
public:
	Model *m_Model;
	std::vector<std::string> m_strAnimationID;
	GLfloat m_fWidth, m_fHeight;

	SpriteObject();
	SpriteObject(unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		GLfloat width, GLfloat height, std::vector<std::string> animationID);
	~SpriteObject();

	void Update(float frameTime);
	void Render(Camera *camera);
};
