#include "stdafx.h"
#include "Witch.h"


#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

#include "BulletSkill.h"
#include "AoeSkill.h"

#include "SoundEngine.h"


Witch::Witch(std::string prefabID, Vector2 roomID, Matrix translationMatrix):Enemy( prefabID,  roomID, translationMatrix)
{
	m_maxHP = 10;
	m_currHP = 10;
	
	m_ATK = 3;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;

	m_MOVESPEED = 2.0f;

	atkDuration = 2.5f;
}

void Witch::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();

	float totalCD = 4.0f;

	//move behavior
	if (m_cState == CS_IDLE || m_cState == CS_MOVE)
	{
		if (distance < 10.0f)
		{
			if (distance < 4.0f && start == false)
			{
				KeepDistance(delta);
				m_MOVESPEED = 4.0f;
			}
			else
				if (currCD <= 0.0f) {

					currCD = totalCD;
					Shoot(plyPos);


				}
				else {

					MoveRandom(frameTime);
					currCD -= frameTime;
				}
		}
		else SetCS(CS_IDLE);

		if (start == true) m_strState = DASH;
	}
	
	
}

void Witch::Shoot(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	BulletSkill* bskill = new BulletSkill(target, this, SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
}

void Witch::Melee(Vector2 target)
{
}
