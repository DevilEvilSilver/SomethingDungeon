#pragma once
#include"stdafx.h"
#include "SpikeTrap.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "CollisionManager.h"

SpikeTrap::SpikeTrap() {}
SpikeTrap::~SpikeTrap() {}

SpikeTrap::SpikeTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = SPIKE;
	m_fTotalCoolDownTime = 2.0f;//theo animation
	m_fCurrFrameTime = 0.0f;
	
}


void SpikeTrap::Update(float frameTime) {
	
	

	if (m_fCurrFrameTime == 0.0f) {

		Player* player = StatePlay::GetInstance()->m_Player;
		Vector2 curPos = Vector2(0.0f,0.0f);


		for (auto& enemy : StatePlay::GetInstance()->m_EnemyList)
		{
			if (StatePlay::GetInstance()->CheckInRange(enemy->m_RoomID))
				if (CollisionManager::CheckCollision(this, enemy))
				{
					enemy->UpdateGotHit(m_iAttack, true, curPos, frameTime);
					
				}

		}

		if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
		{
			StatePlay::GetInstance()->m_Player->UpdateGotHit(m_iAttack, true, curPos, frameTime);
			StatePlay::GetInstance()->m_Player->numHPText->setText("HP: " + std::to_string(StatePlay::GetInstance()->m_Player->m_currHP));
		}

		
	}
	
	m_fCurrFrameTime += frameTime;
	
}



int SpikeTrap::getValueAttack() {
	return m_iAttack;
}