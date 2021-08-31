#include "stdafx.h"
#include "Effect.h"
#include "define.h"
Effect::Effect(Vector2 pos, EffectExistingTime existTime, std::string prefabID, Vector2 roomID, Matrix translationMatrix, Character* victim)
	:Object(prefabID,roomID,translationMatrix)
{
	m_strState = IDLE_LEFT;
	mp_isFisnished = false;
	m_isFacingUp = true;
	m_isFacingLeft = true;

	m_fExistingTime = (float)existTime/1000;
	m_fCurrExistingTime = 0;
	m_Victim = victim;
	Init(pos);
}
void Effect::Init(Vector2 pos)
{
	if (m_Victim != NULL)
	{
		pos = m_Victim->GetCenterPos();
	}
	m_fCurrentPosX = pos.x - m_fWidth / 2;
	m_fCurrentPosY = pos.y - m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;
}
Effect::~Effect()
{

}
void Effect::Update(float frameTime)
{
	m_fCurrFrameTime += frameTime;
	UpdateExistingTime(frameTime);
	UpdatePosition(frameTime);
}
void Effect::UpdateExistingTime(float frameTime)
{
	m_fCurrExistingTime += frameTime;
	if (m_fExistingTime <= m_fCurrExistingTime)
	{
		m_fCurrExistingTime = 0;
		mp_isFisnished = true;
	}
}
void Effect::UpdatePosition(float frametime)
{
	if (m_Victim != NULL)
	{
		Vector2 pos = m_Victim->GetCenterPos();
		m_fCurrentPosX = pos.x - m_fWidth / 2;
		m_fCurrentPosY = pos.y + m_fHeight / 2;
		m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
		m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;
	}
}
