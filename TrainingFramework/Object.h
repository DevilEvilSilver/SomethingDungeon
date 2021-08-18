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

	//GAME
	Vector2 m_RoomID;

	//ANIMATION
	std::string m_strPrefabID;
	std::string m_strState;
	unsigned int m_iCurrFrameIndex;
	float m_fCurrFrameTime;
	bool m_isFacingLeft=true;
	bool m_isFacingUp = true;

	//HITBOX
	unsigned int m_iType;			
	float m_fWidth, m_fHeight;		
	float m_fRadius;				




	virtual void Update(float frameTime);

	//STRUCTOR
	Object();
	Object(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Object();

	//RENDER
	virtual void Render(Camera *camera);
	virtual Matrix GetWorldMatrix();

	//POSITION
	float GetPosX();
	float GetPosY();
	Vector2 GetPos();
	void SetPosX(float x);
	void SetPosY(float y);

	//VELOCITY
	void SetVelocityX(float vx);
	void SetVelocityY(float vy);
	
	//PHYSIC
	float* GetHitBoxCurrentData();



}; 