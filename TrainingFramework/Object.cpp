#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object() {}

Object::Object(std::string prefabID, Matrix worldmatrix,
	unsigned int type, float posX, float posY, float width, float height, float radius)
	: m_strPrefabID(prefabID), m_WorldMatrix(worldmatrix),
	m_iType(type), m_fPosX(posX), m_fPosY(posY), m_fWidth(width), m_fHeight(height), m_fRadius(radius), 
	m_strState("mainIdleLeft"), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {
	
	m_fDeltaX = posX - worldmatrix.m[3][0];
	m_fDeltaY = posY - worldmatrix.m[3][1];
}

Object::~Object() {

}

void Object::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Object::Render(Camera *camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

Matrix Object::GetWorldMatrix() {
	return m_WorldMatrix;
}

float Object::GetPosX() {
	return m_fPosX;
}

float Object::GetPosY() {
	return m_fPosY;
}

void Object::SetPosX(float x) {
	m_fPosX = x;
	m_WorldMatrix.m[3][0] = x - m_fDeltaX;
}

void Object::SetPosY(float y) {
	m_fPosY = y;
	m_WorldMatrix.m[3][1] = y - m_fDeltaY;
}
