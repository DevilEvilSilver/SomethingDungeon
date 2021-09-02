#pragma once
#include "stdafx.h"
#include "CPlant.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"
#include "BulletSkill.h"
#include "AoeSkill.h"
#include "SoundEngine.h"

CPlant::CPlant(std::string prefabID, Vector2 roomID, Matrix translationMatrix) :Witch(prefabID, roomID, translationMatrix)
{
	m_maxHP = CPLANT_HP;
	m_currHP = CPLANT_HP;

	m_ATK = CPLANT_ATK;
	m_DEF = CPLANT_DEF;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;

	m_MOVESPEED = 2.0f;

	atkDuration = 1.0f;

	if (m_HpMob != NULL)
	{
		delete m_HpMob;
		m_HpMob = new EnemyHpMob(roomID, translationMatrix, m_maxHP, m_currHP, 1.0f);
	}
}

void CPlant::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();

	float totalCD = 5.0f;

	//move behavior
	if (m_cState == CS_IDLE || m_cState == CS_MOVE)
	{
		if (distance < 11.0f)
		{
			if (distance < 5.0f && start == false)
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

	if (m_lastMoveDir.x > 0) m_isFacingLeft = true;
	else m_isFacingLeft = false;
	UpdateHpMob(frameTime);

}

void CPlant::Shoot(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	BulletSkill* bskill = new BulletSkill(target, this, SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
	
}

void CPlant::Melee(Vector2 target)
{
}

void CPlant::createDrop()
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
		Gold* gold = new Gold(GOLD, m_RoomID, translation, 15, false);
		StatePlay::GetInstance()->AddDrop(gold);
	}

}