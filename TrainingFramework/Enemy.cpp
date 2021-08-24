#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

#include "BulletSkill.h"
#include "AoeSkill.h"

#include "SoundEngine.h"

void Enemy::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();

	float totalCD = 4.0f;
	
	//move behavior
	m_MOVESPEED = 3.0f;
	
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
	}

	

}

//ACTION
void Enemy::Chase(Vector2 delta)
{
	if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);
	UpdateMoveDirection(delta);
}
void Enemy::KeepDistance(Vector2 delta)
{
	if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);
	UpdateMoveDirection(-delta);
}

bool Enemy::MoveRandom(float frameTime)
{
	

	if (start == false)
	{
		
		ranDir = Vector2(rand()%10, rand()%10);
		if (rand() % 2 == 0) ranDir.x *= -1;
		if (rand() % 2 == 0) ranDir.y *= -1;
		start = true;

		//if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);
		ResetAnimation();
		
	
	}
	if (start == true)
	{
		m_strState = MOVE;
		if (FixedMove(ranDir, m_MOVESPEED, 1.0f, frameTime) == false) return false;
		start = false;
		ResetAnimation();
		return true;
			
		
	}
	

	return false;
}

void Enemy::Shoot(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	BulletSkill* bskill = new BulletSkill(target, this, SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
}

void Enemy::Melee(Vector2 target)
{
	SetCS(CS_ATTACK);

	Matrix m;
	m.SetTranslation(target.x, target.y, 0);

	AoeSkill* bskill = new AoeSkill(target, this, AOE_SKILL, this->m_RoomID, m);
	StatePlay::GetInstance()->AddSkill(bskill);
}

//SKILL
//----------------------------------------

//----------------------------------------

void Enemy::Death(float frameTime)
{
	m_strState = DEATH;
	
	if (FixedMove(Vector2(0,0),0.0f,2.0f, frameTime) == true) {
		SoundEngine::GetInstance()->Play(COIN, 1.0f, 1.0f, false);
		isDead = true;
		createDrop();
	}
}

//OTHER
Enemy::Enemy(){}
Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {

	//m_maxHP = 10;
	//m_currHP = 10;
	//
	//m_ATK = 3;
	//m_DEF = 3;

	//m_strState = IDLE_LEFT;
	//isWallCollision = true;
	//isPlayerCollision = false;
	//isEnemyCollision = true;

	//m_MOVESPEED = 3.0f;

	
	isDead = false;
}
Enemy::~Enemy() {}



void Enemy::createDrop()
{
	unsigned int random = rand() % 100 + 1;

	Matrix translation;
	translation.SetTranslation(GetPosX(), GetPosY(), 0.0f);

	
	if (random >= 75)
	{
		HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(hp);
	}
	else if (random >= 50)
	{
		MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(mp);
	}
	else
	{
		Gold* gold = new Gold(GOLD, m_RoomID, translation, 5, false);
		StatePlay::GetInstance()->AddDrop(gold);
	}
		
}
