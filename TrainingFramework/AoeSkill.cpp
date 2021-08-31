#include "stdafx.h"
#include "AoeSkill.h"
#include "StatePlay.h"
#include "CollisionManager.h"
#include "InputManager.h"

#include "define.h"
AoeSkill::AoeSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix, Vector2 target)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 1.0f;
	m_SkillDamage = SkillDamage::AOE_DAMAGE;
	m_ExsitingTime = SkillExistingTime::AOE_EXISTINGTIME;//ms
	Init(prefabID,target);
	m_damage = owner->m_ATK * (float)m_SkillDamage / 100;

	m_isKnockBack = true;
	/*if (GetPosX() >= owner->GetPosX()) m_isFacingLeft = false;
	else
		m_isFacingLeft = true;
	if (GetPosY() >= owner->GetPosY()) m_isFacingUp = true;*/
}
AoeSkill::AoeSkill(Vector2 tar, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 10.0f;
	m_SkillDamage = SkillDamage::AOE_DAMAGE;
	m_ExsitingTime = SkillExistingTime::AOE_EXISTINGTIME;//ms

	Init(prefabID,tar);

	if (m_fVx > 0) m_isFacingLeft = false;
	m_damage = owner->m_ATK * (float)m_SkillDamage / 100;

	m_isKnockBack = true;
	/*if (tar.x >= owner->GetPosX()) m_isFacingLeft = false;
	else
		m_isFacingLeft = true;
	if (tar.y >= owner->GetPosY()) m_isFacingUp = false;*/
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
					Matrix t; t.SetIdentity();
					Effect* effect = new Effect(Vector2(0, 0), EffectExistingTime::EFFECT_SKILL_EXISTINGTIME, this->m_EffectID, enemy->m_RoomID, t, enemy);
					StatePlay::GetInstance()->AddEffect(effect);
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
	UpdateCurrPos(frameTime);
}
void AoeSkill::UpdateCurrPos(float frameTime)
{
	Vector2 target = m_owner->GetCenterPos() + m_offset;
	m_fCurrentPosX = target.x - m_fWidth / 2;
	m_fCurrentPosY = target.y + m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;

}
void AoeSkill::Init(std::string ID, Vector2 target)
{
	Vector2 dir;
	if (m_isPlayer)
	{
		target = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera, InputManager::GetInstance()->mouseLX, InputManager::GetInstance()->mouseLY);
		dir = target - m_owner->GetCenterPos();
		if (m_isPlayer)
			DirectionPrefab(ID, dir);
	}
	else
	{
		Player* player = StatePlay::GetInstance()->m_Player;
		target = player->GetCenterPos();
	}
	Vector2 c1 = m_owner->GetCenterPos();
	if ((target - c1).Length() > mp_fAoeRadius)
		target = c1 + (target - c1).Normalize() * mp_fAoeRadius;
	m_offset = target - m_owner->GetCenterPos();
	m_fCurrentPosX = target.x - m_fWidth / 2;
	m_fCurrentPosY = target.y + m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;
	m_fVx = 0;
	m_fVy = 0;
}
