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

	m_ATK = 7;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = false;

	m_MOVESPEED = 3.0f;

	m_isInvulnerable = true;
	atkDuration = 1.0f;
}

void RobotKnight::UniqueUpdate(float frameTime)
{
	//printf("boss hp:%d\n", m_currHP);

	switch (m_bState)
	{
	case BS_NORMAL:Normal(frameTime); break;
	case BS_CHARGE:Charge(frameTime); break;
	case BS_ATTACK1:Attack1(frameTime); break;
	case BS_ATTACK2:Attack2(frameTime); break;
	case BS_GUARD:Guard(frameTime); break;
	}
	/*if (m_bState != BS_ATTACK2)
		SetBS(BS_ATTACK2);*/

	
	//printf("robot hp:%d\n", m_currHP);

	if (currAtkCD>0.0f)
	currAtkCD -= frameTime;
}

void RobotKnight::Normal(float frameTime)
{
	m_strState=MOVE;

	if (FixedMove(ranDir, 0.0f, 0.15f, frameTime) == true)
	{
		

		Player* plyr = StatePlay::GetInstance()->m_Player;
		Vector2 plyPos = plyr->GetPos();
		Vector2 enmyPos = GetPos();

		Vector2 delta = plyPos - enmyPos;
		float distance = delta.Length();

		float totalCD = 4.0f;

		if (distance < 20.0f)
		{
			SoundEngine::GetInstance()->Play(BOMB, 1.0f, 2.0f, false);
			if (distance > 5.0f)
			{
				if (rand() % 10 <=4)
					SetBS(BS_CHARGE);
				else SetBS(BS_ATTACK1);

			}
			else
			{
				if (rand() % 10 <= 3)
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
		SoundEngine::GetInstance()->Play(WHOOSH, 1.0f, 0.5f, false);
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
					StatePlay::GetInstance()->m_Player->UpdateGotHit(m_ATK*1.2f, m_isKnockBack, GetPos(), frameTime);
				}					
			}


			if (FixedMove(ranDir, m_MOVESPEED*5.0f, 1.75f, frameTime) == true)
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
	float duration = 1.5f;
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
			float widthRange = 2.75f;
			int pelletRank = 3;
			int bulletWave = 3;
			

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
	float duration = 2.0f;
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
			if (i == 0&&currTime>=1.0f)
			{
				i++;

				Matrix m;
				m.SetTranslation(ranDir.x, ranDir.y, 0);

				int bulletNum = 25;

				Vector2 dir=Vector2(1, 0);

				Vector2 startPos = Vector2(GetPosX() + m_fWidth / 2, GetPosY() - m_fWidth / 2);

				int currNum = bulletNum;
				while (currNum > 0)
				{
					
					dir.x = 1.0f * cos(currNum*360.0f/bulletNum);
					dir.y = 1.0f * sin(currNum*360.0f/bulletNum);

					

					BulletSkill* bskill = new BulletSkill(startPos+dir, this, SKILL, this->m_RoomID, m);
					StatePlay::GetInstance()->AddSkill(bskill);

					currNum--;
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
		//m_isInvincible = true;

		i = 0;
	}
	
	if (start == true)
	{

		switch (i)
		{
		case 0:
			if (FixedMove(ranDir, 0.0f, 0.5f, frameTime) == true)
			{
				i++;
				//m_isInvincible = false;
			}
			break;
		case 1:
			if (FixedMove(ranDir, 0.0f, 1.0f, frameTime) == true)
			{
				SetBS(BS_CHARGE);
				start = false;
			}
			break;
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
