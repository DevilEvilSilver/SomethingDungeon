#include "stdafx.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Prefab.h"
#include "Renderer.h"

template <class T>
T GetResource(std::string id, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (!strcmp(id.c_str(), obj->m_strResourceID.c_str()))
			return obj;
	}
	return 0;
}

Object::Object() {}

Object::Object(std::string prefabID, Matrix translationMatrix)
	: m_strPrefabID(prefabID), m_strState("init"), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {
	Prefab *prefab = GetResource(this->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);
	
	Matrix scaleMatrix;
	scaleMatrix.SetScale(prefab->m_fScaleX, prefab->m_fScaleY, 1.0f);
	m_WorldMatrix = scaleMatrix * translationMatrix;

	m_iType = prefab->m_iType; m_fDeltaX = prefab->m_fDeltaX; m_fDeltaY = prefab->m_fDeltaY;
	m_fWidth = prefab->m_fWidth; m_fHeight = prefab->m_fHeight; m_fRadius = prefab->m_fRadius;
	 
	m_fPosX = m_fDeltaX + m_WorldMatrix.m[3][0];
	m_fPosY = m_fDeltaY + m_WorldMatrix.m[3][1];
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
