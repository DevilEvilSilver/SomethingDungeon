#include "stdafx.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Prefab.h"
#include "Renderer.h"
#include "define.h"

template <class T>
T GetResource(std::string id, std::vector<T> objList) {
	for (auto& obj : objList) {
		if (!strcmp(id.c_str(), obj->m_strResourceID.c_str()))
			return obj;
	}
	return 0;
}

Object::Object() 
{
}

Object::Object(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: m_strPrefabID(prefabID), m_RoomID(roomID), m_strState(INIT_ANIM), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {
	Prefab* prefab = GetResource(this->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);

	Matrix scaleMatrix;
	// Long Chu y bo thuoc tinh m_fDeltaX,m_fDeltaY trong Prefab !!!
	float nothingx, nothingy;


	scaleMatrix.SetScale(prefab->m_fScaleX, prefab->m_fScaleY, 1.0f);
	m_WorldMatrix = scaleMatrix * translationMatrix;

	m_iType = prefab->m_iType; nothingx = prefab->m_fDeltaX; nothingy = prefab->m_fDeltaY;
	m_fWidth = prefab->m_fWidth; m_fHeight = prefab->m_fHeight; m_fRadius = prefab->m_fRadius;
	m_fVx = 0;
	m_fVy = 0;
	m_fCurrentPosX =  m_WorldMatrix.m[3][0];
	m_fCurrentPosY =  m_WorldMatrix.m[3][1];
}

Object::~Object() {

}

void Object::Update(float frameTime) {

}

void Object::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

Matrix Object::GetWorldMatrix() {
	return m_WorldMatrix;
}

float Object::GetPosX() {
	return m_fCurrentPosX;
}

float Object::GetPosY() {
	return m_fCurrentPosY;
}

void Object::SetVelocityX(float vx)
{
	m_fVx = vx;
}
void Object::SetVelocityY(float vy)
{
	m_fVy = vy;
}

void Object::SetPosX(float x)
{
	m_fCurrentPosX = x;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX;
}
void Object::SetPosY(float y)
{
	m_fCurrentPosY = y;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY;
}
float* Object::GetHitBoxCurrentData()
{
	float* data = new float[7]{ m_fCurrentPosX, m_fCurrentPosY, m_fCurrentPosX + m_fWidth, m_fCurrentPosY - m_fHeight,m_fVx,m_fVy, m_fRadius };
	return data;
}
