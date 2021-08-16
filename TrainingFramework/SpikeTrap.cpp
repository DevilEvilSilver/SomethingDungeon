#pragma once
#include"stdafx.h"
#include "SpikeTrap.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

SpikeTrap::SpikeTrap() {}
SpikeTrap::~SpikeTrap() {}

SpikeTrap::SpikeTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int attack)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = SPIKE;
	m_iAttack = attack;
	//m_fCoolDownTime = 0;
}

void SpikeTrap::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void SpikeTrap::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	m_fCoolDownTime -= frameTime;
}

void SpikeTrap::UpdateCollideSpikeTrap(float frameTime, Player* m_Player) {
	if (m_fCoolDownTime <= 0.0f) {
		m_Player->increaseHP(-m_iAttack);
		m_Player->numHPText->setText("HP: " + std::to_string(m_Player->m_iCurHP));
	}
	m_fCoolDownTime = 4.0f;
	m_fCurrFrameTime += frameTime;
}

int SpikeTrap::getValueAttack() {
	return m_iAttack;
}