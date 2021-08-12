#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"


Enemy::Enemy() {}

Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;

	m_MOVESPEED = 10.0f;
}

Enemy::~Enemy() {

}

void Enemy::UsingAI()
{
	Vector2 plyPos = SceneManager::GetInstance()->m_Player->GetPos();
	Vector2 enmyPos = GetPos();

	float distance = (plyPos - enmyPos).Length();

	if (distance < 10.0f) {

		if (distance < 5.0f && distance>2.0f) {
			//float random = rand() % 10;
			if (plyPos.x > enmyPos.x) UpdateMoveDirection(RIGHT);
			if (plyPos.x < enmyPos.x) UpdateMoveDirection(LEFT);

			if (plyPos.y > enmyPos.y) UpdateMoveDirection(UP);
			if (plyPos.y < enmyPos.y) UpdateMoveDirection(DOWN);
		}
	}
}

void Enemy::Update(float frameTime)
{
	m_fCurrFrameTime += frameTime;

	Go(frameTime, true, true, true);
}

void Enemy::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}