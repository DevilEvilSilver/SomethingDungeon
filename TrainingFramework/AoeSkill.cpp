#include "stdafx.h"
#include "AoeSkill.h"
#include "StatePlay.h"
#include "CollisionManager.h"
#include "InputManager.h"

#include "define.h"
AoeSkill::AoeSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix, Vector2 target)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 10.0f;
	m_SkillDamage = SkillDamage::AOE_DAMAGE;
	m_ExsitingTime = SkillExistingTime::AOE_EXISTINGTIME;//ms

	Init(target);

	if (m_fVx > 0) m_isFacingLeft = false;
	m_damage = owner->m_ATK * (float)m_SkillDamage / 100;

	m_isKnockBack = true;
	if (GetPosX() >= owner->GetPosX()) m_isFacingLeft = true;
	if (GetPosY() >= owner->GetPosY()) m_isFacingUp = true;
}
AoeSkill::AoeSkill(Vector2 tar, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 10.0f;
	m_SkillDamage = SkillDamage::AOE_DAMAGE;
	m_ExsitingTime = SkillExistingTime::AOE_EXISTINGTIME;//ms

	Init(tar);

	if (m_fVx > 0) m_isFacingLeft = false;
	m_damage = owner->m_ATK * (float)m_SkillDamage / 100;

	m_isKnockBack = true;
	if (GetPosX() >= owner->GetPosX()) m_isFacingLeft = false;
	if (GetPosY() >= owner->GetPosY()) m_isFacingUp = false;
}
AoeSkill::~AoeSkill()
{
}
void AoeSkill::UpdateHit(float frameTime)
{
	if (m_bHit)
	{
		Vector2 curPos = Vector2(m_fCurrentPosX + m_fDeltaX, m_fCurrentPosY - m_fDeltaY);
		if (m_isPlayer)
		{
			for (auto& enemy : StatePlay::GetInstance()->m_InRangeEnemy)
			{
				if (CollisionManager::CheckCollision(this, enemy))
				{
					enemy->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
					m_bHit = false;
				}
			}
		}
		else
		{
			if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
			{
				m_bHit = false;
				StatePlay::GetInstance()->m_Player->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
			}

		}
	}
}
void AoeSkill::Init(Vector2 target)
{
	if (target.x == 0 || target.y == 0)
	{
		if (m_isPlayer)
			target = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera, InputManager::GetInstance()->mouseLX, InputManager::GetInstance()->mouseLY);
		else
		{
			Player* player = StatePlay::GetInstance()->m_Player;
			target.x = player->GetPosX() + player->m_fWidth / 2;
			target.y = player->GetPosY() - player->m_fHeight / 2;
		}
	}
	float* data1 = m_owner->GetHitBoxCurrentData();
	Vector2 c1(data1[0] + m_owner->m_fWidth / 2, data1[1] - m_owner->m_fHeight / 2);
	if ((target - c1).Length() > mp_fAoeRadius)
		target = c1 + (target - c1).Normalize() * mp_fAoeRadius;
	m_fCurrentPosX = target.x - m_fWidth / 2;
	m_fCurrentPosY = target.y + m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;
	m_fVx = 0;
	m_fVy = 0;
	delete[] data1;
}