#include "stdafx.h"
#include "Frogman.h"

#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

#include "BulletSkill.h"
#include "AoeSkill.h"

#include "SoundEngine.h"

Frogman::Frogman(std::string prefabID, Vector2 roomID, Matrix translationMatrix) :Goblin(prefabID, roomID, translationMatrix)
{
	m_maxHP = 10;
	m_currHP = 10;

	m_ATK = 5;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;

	atkDuration = 1.3f;
	m_MOVESPEED = 1.5f;
}

void Frogman::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();

	float totalCD = 5.0f;
	//move behavior

	m_MOVESPEED = 1.5f;

	if (m_cState == CS_IDLE || m_cState == CS_MOVE)
	{
		if (distance < 10.0f)
		{
			if (currCD <= 0.0f) {
				if (distance >= 0.9f)
				{
					if (distance > 2.0f) m_MOVESPEED = 1.5f;
					else m_MOVESPEED = 2.0f;

					Chase(delta);
				}
				else {
					Melee(plyPos);
					currCD = totalCD;
				}
			}

			else
			{
				m_MOVESPEED = 2.5f;
				MoveRandom(frameTime);
				if (StatePlay::GetInstance()->m_Player->GetPosX() > GetPosX()) m_isFacingLeft = false;
				else m_isFacingLeft = true;
				currCD -= frameTime;
			}
		}
		else SetCS(CS_IDLE);

		if (start == true) m_strState = MOVE;
	}


}

void Frogman::Shoot(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	BulletSkill* bskill = new BulletSkill(target, this, SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
}

void Frogman::Melee(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	AoeSkill* bskill = new AoeSkill(target, this, AOE_SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
}