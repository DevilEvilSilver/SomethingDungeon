#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"

Player::Player() {}

Player::Player(std::string prefabID, Matrix translationMatrix)
	: Character(prefabID, translationMatrix) {

}

Player::~Player() {

}

void Player::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}