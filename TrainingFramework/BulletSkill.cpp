#include "stdafx.h"
#include "BulletSkill.h"
#include "StatePlay.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Room.h"
#include "define.h"
BulletSkill::BulletSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(mousePos,owner,prefabID,roomID,translationMatrix)
{
	m_percentDamage = SkillDamage::BULLET_DAMAGE;
	m_totalExsitingTime = SkillExistingTime::BULLET_EXISTINGTIME;
	mp_MPCost = SkillMPCost::BULLET_MPCOST;
	Init(mousePos);
	m_damage = owner->GetAtk() * (float)m_percentDamage / 100;
}
BulletSkill::~BulletSkill()
{
}

void BulletSkill::UpdateHit(float frameTime)
{
	if (m_isPlayer)
	{
		std::vector<Enemy*> enemyList = StatePlay::GetInstance()->m_EnemyList;
		for (auto& enemy : enemyList)
		{
			if (CollisionManager::CheckCollision(this, enemy))
			{
				//enemy->isAttacked

			}

		}
	}
	else
	{
		if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
		{
			//StatePlay::GetInstance()->m_Player->isAttacked();

		}
	}
	std::vector<Room*> roomList = StatePlay::GetInstance()->m_RoomList;
	for (auto& obj : roomList) {
		if (obj->m_RoomType == WALL)
		{
			if (CollisionManager::CheckCollision(this, obj))
			{
				this->Remove();
			}
		}
	}
}
void BulletSkill::Init(Vector2 mousePos)
{

	float fminDis = 2;
	float* ownerData = m_owner->GetHitBoxCurrentData();
	Vector2 c1(ownerData[0] / 2 + ownerData[2] / 2, ownerData[1] / 2 + ownerData[3] / 2);
	mp_dir = (mousePos - c1).Normalize();
	Vector2 startPos = c1 + mp_dir * fminDis;
	m_fCurrentPosX = startPos.x - m_fWidth / 2;
	m_fCurrentPosY = startPos.y + m_fHeight / 2;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX ;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY + m_fDeltaY ;
	m_fVx = mp_dir.x * BULLET_SPEED;
	m_fVy = mp_dir.y * BULLET_SPEED;
	delete[] ownerData;

}
