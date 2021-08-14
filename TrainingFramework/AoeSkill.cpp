#include "stdafx.h"
#include "AoeSkill.h"
#include "SceneManager.h"
#include "CollisionManager.h"
AoeSkill::AoeSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(mousePos,owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 10;
	m_percentDamage = AOE_DAMAGE;
	m_damage = owner->GetAtk()* (float)m_percentDamage / 100;
	m_currExistingTime = 0;
	m_totalExsitingTime = AOE_EXISTINGTIME;
	mp_MPCost = AOE_MPCOST;
	Init(mousePos);

}
AoeSkill::~AoeSkill()
{
}
//void AoeSkill::Update(float frameTime)
//{
//
//	UpdateHit(frameTime);
//	UpdateMove(frameTime);
//	UpdateExistingTime(frameTime);
//}
void AoeSkill::UpdateHit(float frameTime)
{
	if (m_isPlayer)
	{
		std::vector<Enemy*> enemyList = SceneManager::GetInstance()->m_EnemyList;
		for (auto& enemy : enemyList)
		{
			if (CollisionManager::CheckCollision(this, enemy))
			{
				//enemy->isAttacked
				std::cout << "AoeSkill::Hit		eneny->isAttacked()\n";
			}
		}
	}
	else
	{
		if (CollisionManager::CheckCollision(this, SceneManager::GetInstance()->m_Player))
		{
			//SceneManager::GetInstance()->m_Player->isAttacked
			std::cout << "AoeSkill::Hit	SceneManager::GetInstance()->m_Player->isAttacked()\n";
		}
	}
}
void AoeSkill::Init(Vector2 mousePos)
{
	float* data1 = m_owner->GetHitBoxCurrentData();
	mousePos.x = m_WorldMatrix.m[3][0];
	mousePos.y = m_WorldMatrix.m[3][1];
	Vector2 c1(data1[0] + m_owner->m_fWidth / 2, data1[1] - m_owner->m_fHeight / 2);
	if ((mousePos - c1).Length() > mp_fAoeRadius)
		mousePos = c1 + (mousePos - c1).Normalize() * mp_fAoeRadius;
	m_fCurrentPosX = mousePos.x - m_fWidth / 2;
	m_fCurrentPosY = mousePos.y + m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX - m_WorldMatrix.m[0][0] / 2;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY + m_WorldMatrix.m[1][1] / 2;
	m_fVx = 0;
	m_fVy = 0;
	delete[]data1;
}