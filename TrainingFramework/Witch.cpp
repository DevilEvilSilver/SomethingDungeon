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
	m_maxHP = WITCH_HP;
	m_currHP = WITCH_HP;
	
	m_ATK = WITCH_ATK;
	m_DEF = WITCH_DEF;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;

	m_MOVESPEED = 3.5f;

	atkDuration = 1.0f;

	if (m_HpMob != NULL)
	{
		delete m_HpMob;
		m_HpMob = new EnemyHpMob(roomID, translationMatrix, m_maxHP, m_currHP, 1.0f);
	}
}

void Witch::UniqueUpdate(float frameTime)
{
	UpdateHpMob(frameTime);
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
				m_MOVESPEED = 6.0f;
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

	Vector2 skillWidth = target - GetPos();
	skillWidth.Normalize();
	skillWidth = Vector2(skillWidth.y, -skillWidth.x);

	float widthRange = 2.75f;

	BulletSkill* bskill1 = new BulletSkill(target, this, SKILL, this->m_RoomID, m);
	BulletSkill* bskill2 = new BulletSkill(target - skillWidth * widthRange, this, SKILL, this->m_RoomID, m);
	BulletSkill* bskill3 = new BulletSkill(target + skillWidth * widthRange, this, SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill1);
	StatePlay::GetInstance()->AddSkill(bskill2);
	StatePlay::GetInstance()->AddSkill(bskill3);
}

void Witch::Melee(Vector2 target)
{
}

void Witch::createDrop()
{
	unsigned int random = rand() % 100 + 1;

	Matrix translation;
	translation.SetTranslation(GetCenterPos().x, GetCenterPos().y, 0.0f);


	if (random >= 75)
	{
		MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(mp);
	}
	else
	{
		Gold* gold = new Gold(GOLD, m_RoomID, translation, 20, false);
		StatePlay::GetInstance()->AddDrop(gold);
	}

}