#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Camera.h"

class Object {
public:
	unsigned int m_iModelID;
	std::vector<unsigned int> m_iTexture2DID;
	std::vector<unsigned int> m_iTextureCubeID;
	unsigned int m_iShaderID;
	Matrix m_WorldMatrix;

	Object();
	Object(unsigned int modelID, unsigned int shaderID, Matrix worldMatrix); 
	~Object();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
	Matrix GetWorldMatrix();
}; 