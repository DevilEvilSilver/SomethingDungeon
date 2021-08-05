#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"

Enemy::Enemy() {}

Enemy::Enemy(std::string prefabID, Matrix translationMatrix)
	: Character(prefabID, translationMatrix) {

}

Enemy::~Enemy() {

}

void Enemy::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Enemy::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}