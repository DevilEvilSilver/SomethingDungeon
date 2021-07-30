#pragma once
#include <string>
#include "../Utilities/Math.h"
#include "Camera.h"

class Object {
private:
	float m_fPosX, m_fPosY;
	float m_fDeltaX, m_fDeltaY;

public:
	std::string m_strPrefabID;
	Matrix m_WorldMatrix;

	std::string m_strState;
	unsigned int m_iCurrFrameIndex;
	float m_fCurrFrameTime;

	unsigned int m_iType;			//Collision Shape
	float m_fWidth, m_fHeight;		//For RECT
	float m_fRadius;				//For CIRCLE

	Object();
	Object(std::string prefabID, Matrix worldmatrix,
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