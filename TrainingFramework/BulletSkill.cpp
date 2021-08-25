#include "stdafx.h"
#include "BulletSkill.h"
#include "StatePlay.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Room.h"
#include "define.h"
BulletSkill::BulletSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner,prefabID,roomID,translationMatrix)
{
	m_percentDamage = 100;
	m_totalExsitingTime = 3000;
	mp_MPCost = 1;
	Init(mousePos);
	m_damage = owner->m_ATK * (float)m_percentDamage / 100;
	m_isKnockBack = true;

	if (m_fVx <= 0) m_isFacingLeft = false;
}
BulletSkill::~BulletSkill()
{
}

void BulletSkill::UpdateHit(float frameTime)
{
	
	if (currCD <= 0.0f)
	{
		Vector2 curPos = Vector2(m_fCurrentPosX + m_fDeltaX, m_fCurrentPosY - m_fDeltaY);
		if (m_isPlayer)
		{
			
			for (auto& enemy : StatePlay::GetInstance()->m_InRangeEnemy)
			{

					if (CollisionManager::CheckCollision(this, enemy))
					{
						//enemy->isAttacked
						enemy->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
						
						currCD = totalCD;
					}

			}
		}
		else
		{
			if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
			{
				currCD = totalCD;
				StatePlay::GetInstance()->m_Player->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
				StatePlay::GetInstance()->m_Player->numHPText->setText("HP: " + std::to_string(StatePlay::GetInstance()->m_Player->m_currHP));
			}
		}
	}
	else
	{
		currCD -= frameTime;
		
	}
	
	std::vector<Room*> roomList = StatePlay::GetInstance()->m_InRangeRoom;
	for (auto& obj : roomList) {
		if (obj->m_RoomType == WALL)
		{
			if (CollisionManager::CheckCollision(this, obj))
			{
				isFinished = true;
			}
		}
	}
}
void BulletSkill::Init(Vector2 mousePos)
{

	float fminDis = 0.5f;
	float* ownerData = m_owner->GetHitBoxCurrentData();
	Vector2 c1(ownerData[0] / 2.0f + ownerData[2] / 2.0f, ownerData[1] / 2.0f + ownerData[3] / 2.0f);
	mp_dir = (mousePos - c1).Normalize();
	Vector2 startPos = c1 + mp_dir * fminDis;
	m_fCurrentPosX = startPos.x- m_fWidth / 2.0f;
	m_fCurrentPosY = startPos.y +m_fHeight / 2.0f;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX ;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY - m_fDeltaY ;
	m_fVx = mp_dir.x * BULLET_SPEED;
	m_fVy = mp_dir.y * BULLET_SPEED;
	delete[] ownerData;

}
