#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Camera.h"

class Object {
private:
	float m_fPosX, m_fPosY;
	float m_fDeltaX, m_fDeltaY;

public:
	unsigned int m_iModelID;
	unsigned int m_iShaderID;
	Matrix m_TranslationMatrix;
	Matrix m_RotationMatrix;
	Matrix m_ScaleMatrix;
	Matrix m_WorldMatrix;
	bool m_isNewWorld;

	unsigned int m_iType;
	float m_fWidth, m_fHeight;
	float m_fRadius;

	Object();
	Object(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
		unsigned int type, float posX, float posY, float width, float height, float radius);
	virtual ~Object();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
	Matrix GetWorldMatrix();
	float GetPosX();
	float GetPosY();
	void SetPosX(float x);
	void SetPosY(float y);
}; 