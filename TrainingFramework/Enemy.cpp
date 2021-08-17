#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"


void Enemy::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();

	//move behavior
	if (distance < 5.0f /*&& distance > 5.0f*/) KeepDistance(delta);
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

//SKILL
//----------------------------------------

//----------------------------------------

void Enemy::Death(float frameTime)
{
	printf("dead\n");
	this->createGoldObject();
	StatePlay::GetInstance()->AddDrop(getGold());
	StatePlay::GetInstance()->RemoveEnemy(this);
}

//OTHER
Enemy::Enemy(){}
Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {

	m_maxHP = 10;
	m_currHP = 10;
	
	m_ATK = 3;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = true;
	isEnemyCollision = true;

	m_MOVESPEED = 10.0f;

	m_translationMatrix = translationMatrix;
	isDead = false;
}
Enemy::~Enemy() {}


void Enemy::createGoldObject() {
	Matrix translation = getTranslationMatrix();
	translation.SetTranslation(translation.m[3][0] + 2, translation.m[3][1] + 2, translation.m[3][2]);
	m_gold = new Gold(GOLD, m_RoomID, translation, rand() % 100 + 1, false);
}