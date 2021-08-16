#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"


void Enemy::UniqueUpdate(float frameTime)
{
	Player* plyr = SceneManager::GetInstance()->m_Player;
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
	if (m_cState!=CS_MOVE) SetCS(CS_MOVE);
	UpdateMoveDirection(delta);
}
void Enemy::KeepDistance(Vector2 delta)
{
	if (m_cState != CS_MOVE) SetCS(CS_MOVE);
	UpdateMoveDirection(-delta);
}

//SKILL
//----------------------------------------

//----------------------------------------

//OTHER
Enemy::Enemy(){}
Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
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