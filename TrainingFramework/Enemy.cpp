#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

Enemy::Enemy() {}

Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;
	m_translationMatrix = translationMatrix;
	isDead = false;
}

Enemy::~Enemy() {
	//delete m_gold;
}

void Enemy::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Enemy::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void Enemy::createGoldObject() {
	Matrix translation = getTranslationMatrix();
	translation.SetTranslation(translation.m[3][0] + 2, translation.m[3][1] + 2, translation.m[3][2]);
	m_gold = new Gold(GOLD, m_RoomID, translation, rand() % 100 + 1, false);
}