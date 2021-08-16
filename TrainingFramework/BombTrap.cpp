#pragma once
#include"stdafx.h"
#include "BombTrap.h"
#include "define.h"
#include "ResourceManager.h"
#include "StatePlay.h"
#include "Renderer.h"

BombTrap::BombTrap() {}
BombTrap::~BombTrap() {}

BombTrap::BombTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int attack)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = BOMB_INIT;
	m_iAttack = attack;
	timeTillDelete = 0.8f;
	isCollide = false;
}

void BombTrap::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void BombTrap::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	if (isCollide) {
		timeTillDelete -= frameTime;
	}
	if (timeTillDelete <= 0)
		StatePlay::GetInstance()->removeBombTrap(this);
}

void BombTrap::UpdateCollideBombTrap(float frameTime, Player* m_Player) {
	m_fCurrFrameTime += frameTime;
	m_strState = BOOMED;
	if(!isCollide)
		m_Player->increaseHP(-m_iAttack);		// -hp only once
	isCollide = true;
	m_Player->numHPText->setText("HP: " + std::to_string(m_Player->m_iCurHP));
}

int BombTrap::getValueAttack() {
	return m_iAttack;
}