#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

Player::Player() {}

Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;
}

Player::~Player() {

}

void Player::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}