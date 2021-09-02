#include "stdafx.h"
#include "Skeleton.h"

#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

#include "BulletSkill.h"
#include "AoeSkill.h"

#include "SoundEngine.h"

Skeleton::Skeleton(std::string prefabID, Vector2 roomID, Matrix translationMatrix) :Enemy(prefabID, roomID, translationMatrix)
{
	m_maxHP = 10;
	m_currHP = 10;

	m_ATK = 3;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;
	//m_isKnockBack=true;
	m_MOVESPEED = 2.0f;

	atkDuration = 1.0f;
}


void Skeleton::UniqueUpdate(float frameTime)
{
	UpdateHpMob(frameTime);
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();

	float totalCD = 2.5f;

	
	//move behavior

	if (m_cState == CS_IDLE || m_cState == CS_MOVE)
	{
		if (distance < 10.0f)
		{
			if (currCD <= 0.0f) {
				if (distance >= 0.9f)
				{
					if (distance>2.0f) m_MOVESPEED = 2.0f;
					else m_MOVESPEED = 3.75f;

					Chase(delta);
				}
					
				else {
					if (FixedMove(m_lastMoveDir, 0.0f, delayTime, frameTime) == true)
					{
						Melee(plyPos);
						currCD = totalCD;
					}
				}
			}

			else
			{
				m_MOVESPEED = 4.0f;
				KeepDistance(delta);
				currCD -= frameTime;
			}
		}
		else SetCS(CS_IDLE);

		if (start == true) m_strState = MOVE;
	}

	
}

void Skeleton::Shoot(Vector2 target)
{
}

void Skeleton::Melee(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	AoeSkill* bskill = new AoeSkill(target, this, AOE_SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
}
