#include "stdafx.h"
#include "AoeSkill.h"
#include "SceneManager.h"
#include "CollisionManager.h"
AoeSkill::AoeSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	m_currExistingTime = 0;
	m_totalExsitingTime = AOE_EXISTINGTIME;
	m_MPCost = AOE_MPCOST;
}
AoeSkill::~AoeSkill()
{
}
void AoeSkill::Update(float frameTime)
{

	UpdateHit(frameTime);
	UpdateMove(frameTime);
	UpdateExistingTime(frameTime);
}
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
void AoeSkill::UpdateMove(float frameTime)
{

}