#pragma once
#include"stdafx.h"
#include "BombTrap.h"
#include "define.h"
#include "ResourceManager.h"
#include "StatePlay.h"
#include "Renderer.h"

#include "CollisionManager.h"

#include "SoundEngine.h"

BombTrap::~BombTrap() {}

BombTrap::BombTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = BOMB_INIT;

	timeTillDelete = 0.8f;
	isCollide = false;

	
}



void BombTrap::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	
	if (isCollide==false)
	{
	

			if (isCollide == false)
			{
				for (auto& obj : StatePlay::GetInstance()->m_InRangeSkill)
					if (CollisionManager::CheckCollision(this, obj, frameTime)) isCollide = true;
			}
		
		


		if (isCollide==true) {
			m_strState = BOOMED;
			SoundEngine::GetInstance()->Play(BOMB, 1.0f, 1.0f, false);
		}

		
		
	}
	else
	if (isCollide) {
		timeTillDelete -= frameTime;
	}
	if (timeTillDelete <= 0) 
	{
		Player* player = StatePlay::GetInstance()->m_Player;
		Vector2 curPos = Vector2(m_fCurrentPosX + m_fDeltaX, m_fCurrentPosY - m_fDeltaY);


		for (auto& enemy : StatePlay::GetInstance()->m_InRangeEnemy)
		{
				if (CollisionManager::CheckCollision(this, enemy))
				{
					enemy->UpdateGotHit(m_iAttack, true, curPos, frameTime);
					printf("enemy hp:%d\n", enemy->m_currHP);
				}
		}
		
		if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
		{
			StatePlay::GetInstance()->m_Player->UpdateGotHit(m_iAttack, true, curPos, frameTime);
			StatePlay::GetInstance()->m_Player->numHPText->setText("HP: " + std::to_string(StatePlay::GetInstance()->m_Player->m_currHP));
		}


		isExploded = true;



	}
		
}



int BombTrap::getValueAttack() {
	return m_iAttack;
}