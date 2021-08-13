#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"


Enemy::Enemy() {
	
}

Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;
	isWallCollision = true;
	isPlayerCollision = true;
	isEnemyCollision = true;

	m_MOVESPEED = 10.0f;
}

Enemy::~Enemy() {

}

void Enemy::UsingAI()
{
	Player* plyr = SceneManager::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();


	//move behavior
	if (distance < 7.0f&&distance > 2.0f) Chase(delta);
}

void Enemy::Chase(Vector2 delta)
{
	UpdateMoveDirection(delta);
}
void Enemy::KeepDistance(Vector2 delta)
{
	UpdateMoveDirection(-delta);
}

void Enemy::Update(float frameTime)
{
	m_fCurrFrameTime += frameTime;

	if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
	{
		m_lastMoveDir = m_moveDir;
		UpdatePosition(m_MOVESPEED, frameTime);
	}

	
}

void Enemy::Render(Camera* camera) 
{
	Renderer::GetInstance()->DrawAnimated(this, camera);
}