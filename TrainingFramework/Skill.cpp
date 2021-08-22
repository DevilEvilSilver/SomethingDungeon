
#include "stdafx.h"
#include "Skill.h"
#include "Camera.h"
#include "Renderer.h"
#include "define.h"
#include "StatePlay.h"

Skill::Skill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Object(prefabID, roomID, translationMatrix)
{
	if (owner == StatePlay::GetInstance()->m_Player)
		m_isPlayer = true;
	else
		m_isPlayer = false;

	m_strState = IDLE_LEFT;

	m_owner = owner;
	
	m_currExistingTime = 0;
}

Skill::~Skill()
{
}
void Skill::Update(float frameTime)
{
	UpdateHit(frameTime);
	UpdateMove(frameTime);
	UpdateExistingTime(frameTime);

	m_fCurrFrameTime += frameTime;
}
void Skill::UpdateMove(float frameTime)
{
	if (m_fVx || m_fVy)
	{
		m_fCurrentPosX += m_fVx * frameTime;
	m_fCurrentPosY += m_fVy * frameTime;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX ;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY ;
	}
}
void Skill::UpdateHit(float frameTime){}

void Skill::Render(Camera* camera)
{
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
void Skill::UpdateExistingTime(float frameTime)
{
	m_currExistingTime += frameTime;
	if (m_currExistingTime > (float)m_totalExsitingTime / 1000)
	{
		isFinished = true;
		
	}
}

void Skill::Init(Vector2 mousePos)
{

}