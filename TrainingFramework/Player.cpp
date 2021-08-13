#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

Player::Player() {}

Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;

	m_inumGold = 0;
	std::string goldText = "Gold: " + std::to_string(m_inumGold);
	numGoldText = new Text(goldText, 1, 1, TEXT_COLOR::GREEN, 20, 40, 1.0f);

	m_iCurHP = 100;
	std::string Hptext = "HP: " + std::to_string(m_iCurHP);
	numHPText = new Text(Hptext, 1, 1, TEXT_COLOR::RED, 20, 60, 1.0f);
}

Player::~Player() {
	delete numGoldText;
	delete numHPText;
}

void Player::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	SetPosX(GetPosX() + m_fVx * frameTime);
	SetPosY(GetPosY() + m_fVy * frameTime);
}

void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
	Renderer::GetInstance()->DrawText2(numGoldText);
	Renderer::GetInstance()->DrawText2(numHPText);
}


void Player::increaseGold(Gold* gold) {
	m_inumGold += gold->getValue();
}

void Player::increaseGold(int value) {
	m_inumGold += value;
}

void Player::increaseHP(int numHP) {
	m_iCurHP += numHP;
}
