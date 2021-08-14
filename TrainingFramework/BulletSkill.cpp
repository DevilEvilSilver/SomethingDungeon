#include "stdafx.h"
#include "BulletSkill.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
BulletSkill::BulletSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(mousePos,owner,prefabID,roomID,translationMatrix)
{

}
BulletSkill::~BulletSkill()
{
}
void BulletSkill::Update(float frameTime)
{
	UpdateHit(frameTime);
	UpdateMove(frameTime);
	UpdateExistingTime(frameTime);
}
void BulletSkill::UpdateHit(float frameTime)
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
void BulletSkill::Init()
{

}
