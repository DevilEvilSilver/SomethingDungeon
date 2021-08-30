
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
	m_isKnockBack = false;
	m_bHit = true;
	isFinished = false;
	InitEffect(prefabID);
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
		m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
		m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;
	}
}
void Skill::UpdateHit(float frameTime) {}

void Skill::Render(Camera* camera)
{
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
void Skill::UpdateExistingTime(float frameTime)
{
	m_currExistingTime += frameTime;
	if (m_currExistingTime > (float)m_ExsitingTime / 1000)
	{
		isFinished = true;
	}
}

void Skill::Init(Vector2 mousePos)
{

}
void Skill::InitEffect(std::string prefabID)
{
	//FIRE
	if (prefabID == SKILL_FIRE1)
		m_EffectID = EFFECT_SKILL_FIRE1;
	else if (prefabID == SKILL_FIRE2)
		m_EffectID = EFFECT_SKILL_FIRE2;
	else if (prefabID == SKILL_FIRE3)
		m_EffectID = EFFECT_SKILL_FIRE3;
	//FREEZE
	else if (prefabID == SKILL_FREEZE1)
		m_EffectID = EFFECT_SKILL_FREEZE1;
	else if (prefabID == SKILL_FREEZE2)
		m_EffectID = EFFECT_SKILL_FREEZE2;
	else if (prefabID == SKILL_FREEZE3)
		m_EffectID = EFFECT_SKILL_FREEZE3;
	//WIND
	/*else if (prefabID == SKILL_WIND1)
		m_EffectID = EFFECT_SKILL_WIND1;
	else if (prefabID == SKILL_WIND2)
		m_EffectID = EFFECT_SKILL_WIND2;
	else if (prefabID == SKILL_WIND3)
		m_EffectID = EFFECT_SKILL_WIND3;*/
}