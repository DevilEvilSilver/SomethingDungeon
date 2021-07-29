#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Camera.h"

class Object {
public:
	unsigned int m_iModelID;
	unsigned int m_iShaderID;
	Matrix m_TranslationMatrix;
	Matrix m_RotationMatrix;
	Matrix m_ScaleMatrix;
	Matrix m_WorldMatrix;
	bool m_isNewWorld;

	Object();
	Object(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix);
	virtual ~Object();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
	Matrix GetWorldMatrix();
	float GetPosX();
	float GetPosY();
	void SetPosX(float x);
	void SetPosY(float y);
}; 