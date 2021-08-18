#include "stdafx.h"
#include "AoeSkill.h"
#include "StatePlay.h"
#include "CollisionManager.h"


#include "define.h"
AoeSkill::AoeSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	mp_fAoeRadius = 2.0f;
	m_percentDamage = 150.0f;
	m_totalExsitingTime = 500.0f;//ms

	Init(mousePos);

	if (m_fVx > 0) m_isFacingLeft = false;
	m_damage = owner->m_ATK * (float)m_percentDamage / 100;
	
	m_isKnockBack = true;
	totalCD = 5.0f;
	if (GetPosX() >= owner->GetPosX()) m_isFacingLeft = false;
	if (GetPosY() >= owner->GetPosY()) m_isFacingUp = false;
}
AoeSkill::~AoeSkill()
{
}
void AoeSkill::UpdateHit(float frameTime)
{
	if (currCD <= 0.0f)
	{
		Vector2 curPos = Vector2(m_fCurrentPosX + m_fDeltaX, m_fCurrentPosY - m_fDeltaY);
		if (m_isPlayer)
		{


			for (auto& enemy : StatePlay::GetInstance()->m_EnemyList)
			{
				if (StatePlay::GetInstance()->CheckInRange(enemy->m_RoomID))
					if (CollisionManager::CheckCollision(this, enemy))
					{
						enemy->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
						

						currCD = totalCD;
					}
			}
		}
		else
			if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
			{
				currCD = totalCD;
				StatePlay::GetInstance()->m_Player->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
				StatePlay::GetInstance()->m_Player->numHPText->setText("HP: " + std::to_string(StatePlay::GetInstance()->m_Player->m_currHP));
			}
	}
	else 
	{
		currCD -= frameTime;
		
	}
			


}
void AoeSkill::Init(Vector2 mousePos)
{
	float* data1 = m_owner->GetHitBoxCurrentData();
	Vector2 c1(data1[0]+ m_owner->m_fWidth / 2, data1[1]- m_owner->m_fHeight / 2);
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