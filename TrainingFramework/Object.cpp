#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object() {}

Object::Object(std::string prefabID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix,
	unsigned int type, float posX, float posY, float width, float height, float radius)
	: m_strPrefabID(prefabID), m_TranslationMatrix(translationMatrix), m_RotationMatrix(rotationMatrix), m_ScaleMatrix(scaleMatrix), 
	m_isNewWorld(true), m_iType(type), m_fPosX(posX), m_fPosY(posY), m_fWidth(width), m_fHeight(height), m_fRadius(radius), 
	m_strState("mainIdleLeft"), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {
	
	m_fDeltaX = m_fPosX - m_TranslationMatrix.m[3][0];
	m_fDeltaY = m_fPosY - m_TranslationMatrix.m[3][1];
}

Object::~Object() {

}

void Object::Update(float frameTime) {

}

void Object::Render(Camera *camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

Matrix Object::GetWorldMatrix() {
	if (m_isNewWorld) {
		m_WorldMatrix = m_ScaleMatrix * m_RotationMatrix * m_TranslationMatrix;
		m_isNewWorld = false;
	}
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
	m_TranslationMatrix.m[3][0] = x - m_fDeltaX;
	m_isNewWorld = true;
}

void Object::SetPosY(float y) {
	float deltaY = m_fPosY - m_TranslationMatrix.m[3][1];
	m_fPosY = y;
	m_TranslationMatrix.m[3][1] = y - m_fDeltaY;
	m_isNewWorld = true;
}
