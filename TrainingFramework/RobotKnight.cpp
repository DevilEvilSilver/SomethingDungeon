#include "stdafx.h"
#include "RobotKnight.h"

#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

#include "BulletSkill.h"
#include "AoeSkill.h"

#include "SoundEngine.h"


#define A_CHARGE		"charge"
#define A_GUARD			"guard"
#define A_ATTACK2		"attack2"

RobotKnight::RobotKnight(std::string prefabID, Vector2 roomID, Matrix translationMatrix) :Enemy(prefabID, roomID, translationMatrix)
{
	m_maxHP = 100;
	m_currHP = 100;

	m_ATK = 3;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;

	m_MOVESPEED = 3.0f;

	m_isInvulnerable = true;
	atkDuration = 1.0f;
}

void RobotKnight::UniqueUpdate(float frameTime)
{
	printf("boss hp:%d\n", m_currHP);

	switch (m_bState)
	{
	case BS_NORMAL:Normal(frameTime); break;
	case BS_CHARGE:Charge(frameTime); break;
	case BS_ATTACK1:Attack1(frameTime); break;
	case BS_ATTACK2:Attack2(frameTime); break;
	case BS_GUARD:Guard(frameTime); break;
	}


	if (currAtkCD>0.0f)
	currAtkCD -= frameTime;
}

void RobotKnight::Normal(float frameTime)
{
	m_strState=MOVE;

	if (FixedMove(ranDir, 0.0f, 0.75f, frameTime) == true)
	{
		

		Player* plyr = StatePlay::GetInstance()->m_Player;
		Vector2 plyPos = plyr->GetPos();
		Vector2 enmyPos = GetPos();

		Vector2 delta = plyPos - enmyPos;
		float distance = delta.Length();

		float totalCD = 4.0f;

		if (distance < 20.0f)
		{
			if (distance > 7.0f)
			{
				if (rand() % 2 == 0)
					SetBS(BS_CHARGE);
				else SetBS(BS_ATTACK1);

			}
			else
			{
				if (rand() % 2 == 0)
					SetBS(BS_GUARD);
				else SetBS(BS_ATTACK2);
			}
		}
	}

}

void RobotKnight::Charge(float frameTime)
{

	if (start == false)
	{
		start = true;
		i = 0;
		ranDir = StatePlay::GetInstance()->m_Player->GetPos() - GetPos();
		ranDir.x -= m_fWidth / 2.0f+ StatePlay::GetInstance()->m_Player->m_fWidth/2.0f;
		ranDir.y += m_fHeight / 2.0f - StatePlay::GetInstance()->m_Player->m_fHeight / 2.0f;
	}
	
	if (start==true)
	{
		switch (i)
		{
		case 0:
			m_strState = A_CHARGE;

			if (currAtkCD <= 0.0f)
			{
				
				if (CollisionManager::CheckCollision(StatePlay::GetInstance()->m_Player, this, 0.0f) == true)
				{
					currAtkCD = totalAtkCD;
					StatePlay::GetInstance()->m_Player->UpdateGotHit(5, m_isKnockBack, GetPos(), frameTime);
				}
					
			}

			if (FixedMove(ranDir, m_MOVESPEED*5.0f, 2.0f, frameTime) == true)
			{
				i++;
			}
			break;
		case 1:
			
			start = false;
			SetBS(BS_NORMAL);
			break;
		}
	}
	
	if (ranDir.x > 0.0f) m_isFacingLeft = false;
	else m_isFacingLeft = true;

}

void RobotKnight::Attack1(float frameTime)
{
	float duration = 3.0f;
	m_strState = ATTACK;

	if (start == false)
	{
		start = true;
		i = 0;
		ranDir = StatePlay::GetInstance()->m_Player->GetPos();

	}
	
	if (start == true)
	{
		

		if (FixedMove(ranDir, 0.0f, duration, frameTime) == true)
		{
			start = false;
			SetBS(BS_NORMAL);
		}
		else
		{
			Matrix m;
			m.SetTranslation(ranDir.x, ranDir.y, 0);

			Vector2 skillWidth = ranDir - GetPos();
			skillWidth.Normalize();
			skillWidth = Vector2(skillWidth.y, -skillWidth.x);
			float widthRange = 2.5f;
			int pelletRank = 3;
			int bulletWave = 4;
			

			if (i < bulletWave)
			{
				if (currTime > 0.25f*duration/bulletWave*(i+0.85f))
				{
					while (pelletRank >= 0)
					{
						BulletSkill* bskill = new BulletSkill(ranDir + skillWidth * widthRange * pelletRank, this, SKILL, this->m_RoomID, m);
						StatePlay::GetInstance()->AddSkill(bskill);

						bskill = new BulletSkill(ranDir - skillWidth * widthRange * pelletRank, this, SKILL, this->m_RoomID, m);
						StatePlay::GetInstance()->AddSkill(bskill);

						pelletRank--;
					}

					i++;
				}
			}

		}
			
	}

	if (ranDir.x > GetPosX()) m_isFacingLeft = false;
	else m_isFacingLeft = true;
}

void RobotKnight::Attack2(float frameTime)
{
	float duration = 3.0f;
	m_strState = A_ATTACK2;
	if (start == false)
	{
		start = true;
		i = 0;
		ranDir = StatePlay::GetInstance()->m_Player->GetPos();

	}

	if (start == true)
	{
		

		if (FixedMove(ranDir, 0.0f, duration, frameTime) == true)
		{	
			start = false;
			SetBS(BS_NORMAL);
		}
		else
		{
			if (i == 0&&currTime>0.5f)
			{
				i++;

				Matrix m;
				m.SetTranslation(ranDir.x, ranDir.y, 0);

				Vector2 skillWidth = ranDir - GetPos();
				skillWidth.Normalize();
				skillWidth = Vector2(skillWidth.y, -skillWidth.x);
				float widthRange = 2.5f;
				int pelletRank = 5;
				int bulletWave = 4;



				while (pelletRank >= 0)
				{
					BulletSkill* bskill = new BulletSkill(ranDir + skillWidth * widthRange * pelletRank, this, SKILL, this->m_RoomID, m);
					StatePlay::GetInstance()->AddSkill(bskill);

					bskill = new BulletSkill(ranDir - skillWidth * widthRange * pelletRank, this, SKILL, this->m_RoomID, m);
					StatePlay::GetInstance()->AddSkill(bskill);

					pelletRank--;
				}
			}
		}
	}

	if (ranDir.x > GetPosX()) m_isFacingLeft = false;
	else m_isFacingLeft = true;
}



void RobotKnight::Guard(float frameTime)
{
	m_strState = A_GUARD;
	if (start == false)
	{
		start = true;
		ranDir = StatePlay::GetInstance()->m_Player->GetPos();
		m_isInvincible = true;
	}
	
	if (start == true)
	{
		if (FixedMove(ranDir, 0.0f, 3.0f, frameTime) == true)
		{

			m_isInvincible = false;

			SetBS(BS_CHARGE);
			start = false;
		}
		
		
	}
	
	
	if (ranDir.x > GetPosX()) m_isFacingLeft = false;
	else m_isFacingLeft = true;

}

void RobotKnight::SetBS(BossState bs)
{
	m_bState = bs;
	ResetAnimation();
}

void RobotKnight::Shoot(Vector2 target)
{
}

void RobotKnight::Melee(Vector2 target)
{
}
