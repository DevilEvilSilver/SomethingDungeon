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
	m_iAttack = TRAP_SPIKE_ATK;
}


void SpikeTrap::Update(float frameTime) {
	
	

	if (m_iCurrFrameIndex == 2&&m_fCurrCD <= 0.0f) {
		m_fCurrCD = m_fTotalCoolDownTime;

		Player* player = StatePlay::GetInstance()->m_Player;
		Vector2 curPos = Vector2(0.0f,0.0f);


		for (auto& enemy : StatePlay::GetInstance()->m_InRangeEnemy)
		{

				if (CollisionManager::CheckCollision(this, enemy))
				{
					enemy->UpdateGotHit(getValueAttack(), true, curPos, frameTime);
					
				}

		}

		if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
		{
			StatePlay::GetInstance()->m_Player->UpdateGotHit(getValueAttack(), true, curPos, frameTime);
		}

		
	}
	else 
	{
		m_fCurrCD -= frameTime;
		m_fCurrFrameTime += frameTime;

	}
	
	
	
}



int SpikeTrap::getValueAttack() {
	return m_iAttack;
}