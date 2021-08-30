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
	: m_strPrefabID(prefabID), m_RoomID(roomID), m_strState(INIT_ANIM), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0), m_fVx(0.0f), m_fVy(0.0f) {
	Prefab* prefab = GetResource(this->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);

	Matrix scaleMatrix;

	scaleMatrix.SetScale(prefab->m_fScaleX, prefab->m_fScaleY, 1.0f);
	m_WorldMatrix = scaleMatrix * translationMatrix;

	//CHECK!!!!!!!!!!!!!!!!!!!!
	m_iType = prefab->m_iType; 
	m_fDeltaX = prefab->m_fDeltaX; m_fDeltaY = prefab->m_fDeltaY;
	//CHECK!!!!!!!!!!!!!!!!!!!!!!!

	m_fWidth = prefab->m_fWidth; m_fHeight = prefab->m_fHeight; m_fRadius = prefab->m_fRadius;
	m_fVx = 0;
	m_fVy = 0;
	m_fCurrentPosX =  m_WorldMatrix.m[3][0]+ prefab->m_fDeltaX;
	m_fCurrentPosY =  m_WorldMatrix.m[3][1]- prefab->m_fDeltaY;
}

Object::~Object() {

}

void Object::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Object::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

Matrix Object::GetWorldMatrix() {
	return m_WorldMatrix;
}

//POSITION
	//GET 
	float Object::GetPosX() {
		return m_fCurrentPosX;
	}
	float Object::GetPosY() {
		return m_fCurrentPosY;
	}
	Vector2 Object::GetPos()
	{

		return Vector2(m_fCurrentPosX, m_fCurrentPosY);
	}
	Vector2 Object::GetCenterPos()
	{
		return Vector2(m_fCurrentPosX + m_fWidth/2, m_fCurrentPosY - m_fHeight/2);
	}
	Vector2 Object::GetVelocity()
	{
		return Vector2(m_fVx, m_fVy);
	}
	//SET

	void Object::SetPosX(float x)
	{

		m_fCurrentPosX = x;
		m_WorldMatrix.m[3][0] = x - m_fDeltaX;
	}
	void Object::SetPosY(float y)
	{
		float fDeltaY = m_fCurrentPosY - m_WorldMatrix.m[3][1];
		m_fCurrentPosY = y;
		m_WorldMatrix.m[3][1] = y + m_fDeltaY;
	}

	void Object::SetDeltaY(float y)
	{
		m_fDeltaY = y;
	}

	void Object::SetPosY2(float y)
	{
		m_fCurrentPosY = y;
	}

//SET VELOCITY
void Object::SetVelocityX(float vx)
{
	m_fVx = vx;
}
void Object::SetVelocityY(float vy)
{
	m_fVy = vy;
}

float* Object::GetHitBoxCurrentData()
{
	float* data = new float[8]{ m_fCurrentPosX, m_fCurrentPosY,
								m_fCurrentPosX + m_fWidth, m_fCurrentPosY - m_fHeight,
								m_fVx,m_fVy, 
								m_fCurrentPosX + m_fWidth/2, m_fCurrentPosY - m_fHeight/2 };// center positon
	return data;
}

