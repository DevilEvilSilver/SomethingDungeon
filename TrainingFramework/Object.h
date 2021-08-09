#pragma once
#include <string>
#include "../Utilities/Math.h"
#include "Camera.h"

class Object {
protected:
	Matrix m_WorldMatrix;
	float m_fPosX, m_fPosY;
	float m_fDeltaX, m_fDeltaY;

public:
	std::string m_strPrefabID;
	Vector2 m_RoomID;

	//Animation info
	std::string m_strState;
	unsigned int m_iCurrFrameIndex;
	float m_fCurrFrameTime;

	//Hitbox info
	unsigned int m_iType;			
	float m_fWidth, m_fHeight;		
	float m_fRadius;				

	Object();
	Object(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Object();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
	Matrix GetWorldMatrix();
	float GetPosX();
	float GetPosY();
	void SetPosX(float x);
	void SetPosY(float y);

	float* GetHitBoxData();
}; 