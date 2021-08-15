#pragma once
#include <string>
#include "../Utilities/Math.h"
#include "Camera.h"
#include <iostream>

class Object {
protected:
	Matrix m_WorldMatrix;
	float m_fCurrentPosX, m_fCurrentPosY;
	float m_fVx, m_fVy;
	float m_fDeltaX, m_fDeltaY;
public:
	std::string m_strPrefabID;
	Vector2 m_RoomID;

	//Animation info
	std::string m_strState;
	unsigned int m_iCurrFrameIndex;
	float m_fCurrFrameTime;
	bool m_isFacingLeft=true;

	//Hitbox info
	unsigned int m_iType;			
	float m_fWidth, m_fHeight;		
	float m_fRadius;				
	float m_nothingx, m_nothingy;

	Object();
	Object(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Object();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
	Matrix GetWorldMatrix();
	
	float GetPosX();
	float GetPosY();
	void SetVelocityX(float vx);
	void SetVelocityY(float vy);
	void SetPosX(float x);
	void SetPosY(float y);
	// PhysicEngine
	float* GetHitBoxCurrentData();


	//new
	Vector2 GetPos();
}; 