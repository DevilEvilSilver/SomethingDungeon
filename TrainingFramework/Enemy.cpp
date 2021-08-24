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
Enemy::Enemy() {}
Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {

	m_maxHP = 10;
	m_currHP = 10;

	m_ATK = 3;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = false;
	isEnemyCollision = true;

	m_MOVESPEED = 3.0f;


	isDead = false;
}
Enemy::~Enemy() {}
void Enemy::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();
	
	//move behavior
	m_MOVESPEED = 3.0f;
	if (distance < 4.0f /*&& distance > 5.0f*/)
	{
		KeepDistance(delta);
		m_MOVESPEED = 4.0f;
	}
		
	else if (distance < 10.0f)
	{
		
		//if (currCD <= 0.0f) {
		//	currCD = totalCD;
		//	//ShootChicken(plyPos);
		//}
		//else {
		//	MoveRandom(frameTime);

		//	//currCD -= frameTime;
		//}
	}
	else SetCS(CS_IDLE);

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
	if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);

	if (start == false)
	{
		
		ranDir = Vector2(rand()%10, rand()%10);
		if (rand() % 2 == 0) ranDir.x *= -1;
		if (rand() % 2 == 0) ranDir.y *= -1;
		start = true;
	
	}
	if (start == true)
	{
		if (FixedMove(ranDir, m_MOVESPEED, 1.0f, frameTime) == false) return false;
		start = false;
		return true;
			
		
	}
	

	return false;
}

//SKILL
//----------------------------------------

//----------------------------------------

void Enemy::Death(float frameTime)
{
	m_strState = DASH;
	
	isDead = true;
	SoundEngine::GetInstance()->Play(COIN, 1.0f, 1.0f, false);

	createDrop();

}

//OTHER



void Enemy::createGoldObject() {

	Matrix translation;
	translation.SetTranslation(GetPosX(), GetPosY(), 0.0f);
	m_gold = new Gold(GOLD, m_RoomID, translation, 5, false);
}

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
