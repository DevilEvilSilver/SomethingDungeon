#include "stdafx.h"
#include "AoeSkill.h"
#include "StatePlay.h"
#include "CollisionManager.h"
AoeSkill::AoeSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(mousePos,owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 10;
	m_percentDamage = SkillDamage::AOE_DAMAGE;
	m_totalExsitingTime = SkillExistingTime::AOE_EXISTINGTIME;
	mp_MPCost = SkillMPCost::AOE_MPCOST;
	Init(mousePos);
	m_damage = owner->GetAtk() * (float)m_percentDamage / 100;
}
AoeSkill::~AoeSkill()
{
}
void AoeSkill::UpdateHit(float frameTime)
{
	if (m_isPlayer)
	{
		std::vector<Enemy*> enemyList = StatePlay::GetInstance()->m_EnemyList;
		for (auto& enemy : enemyList)
		{
			if (CollisionManager::CheckCollision(this, enemy))
			{
				//enemy->isAttacked
				//std::cout << "AoeSkill::Hit		eneny->isAttacked()\n";
			}
		}
	}
	else
	{
		if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
		{
			//StatePlay::GetInstance()->m_Player->isAttacked
			//std::cout << "AoeSkill::Hit	StatePlay::GetInstance()->m_Player->isAttacked()\n";
		}
	}
}
void AoeSkill::Init(Vector2 mousePos)
{
	float* data1 = m_owner->GetHitBoxCurrentData();
	Vector2 c1(data1[0] + m_owner->m_fWidth / 2, data1[1] - m_owner->m_fHeight / 2);
	if ((mousePos - c1).Length() > mp_fAoeRadius)
		mousePos = c1 + (mousePos - c1).Normalize() * mp_fAoeRadius;
	m_fCurrentPosX = mousePos.x - m_fWidth / 2;
	m_fCurrentPosY = mousePos.y + m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY;
	m_fVx = 0;
	m_fVy = 0;
	delete[] data1;
}