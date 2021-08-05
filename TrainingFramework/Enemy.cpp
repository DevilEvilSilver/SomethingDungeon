#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

Enemy::Enemy() {}

Enemy::Enemy(std::string prefabID, Matrix translationMatrix)
	: Character(prefabID, translationMatrix) {
	m_strState = IDLE_LEFT;
}

Enemy::~Enemy() {

}

void Enemy::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Enemy::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}