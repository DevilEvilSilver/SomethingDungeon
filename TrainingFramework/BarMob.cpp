#include "stdafx.h"
#include "BarMob.h"
#include "Renderer.h"
#include "define.h"
BarMob::BarMob()
{

}
BarMob::BarMob(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue, float barSize)
	:Object(prefabID, roomID, translationMatrix)
{
	m_strState = INIT_ANIM;
	m_fMaxValue = maxValue;
	m_WorldMatrix.m[0][0] *= barSize;
	m_WorldMatrix.m[1][1] *= 1;
	m_fBarSize = m_WorldMatrix.m[0][0];
	Resize(currValue);
}
BarMob::~BarMob()
{

}

void BarMob::Update(float frameTime)
{
	m_fCurrFrameTime += frameTime;
}
void BarMob::Render(Camera* camera)
{
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
Matrix BarMob::GetWorldMatrix(Camera* camera)
{
	return m_WorldMatrix;
}

void BarMob::SetWorldPos(Vector2 pos)
{
	SetPosX(pos.x);
	SetPosY(pos.y);
}
void BarMob::Resize(float value)
{
	float ratio = max(min(value / m_fMaxValue, 1.0f), 0.0f);
	m_WorldMatrix.m[0][0] = ratio * m_fBarSize;
}