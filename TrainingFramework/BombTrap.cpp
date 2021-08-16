#pragma once
#include"stdafx.h"
#include "BombTrap.h"
#include "define.h"
#include "ResourceManager.h"
#include "StatePlay.h"
#include "Renderer.h"

#include "CollisionManager.h"

BombTrap::~BombTrap() {}

BombTrap::BombTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = BOMB_INIT;

	timeTillDelete = 0.8f;
	isCollide = false;
}



void BombTrap::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;

	if (isCollide==false&&CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player, frameTime))
	{
		m_fCurrFrameTime += frameTime;
		m_strState = BOOMED;
		if (!isCollide)
				// -hp only once
		isCollide = true;
		
	}
	else
	if (isCollide) {
		timeTillDelete -= frameTime;
	}
	if (timeTillDelete <= 0) {
		Player* player = StatePlay::GetInstance()->m_Player;
		Vector2 curPos = Vector2(m_fCurrentPosX + m_fDeltaX, m_fCurrentPosY - m_fDeltaY);

		player->UpdateGotHit(m_iAttack,true,curPos,frameTime);
		StatePlay::GetInstance()->m_Player->numHPText->setText("HP: " + std::to_string(StatePlay::GetInstance()->m_Player->m_currHP));


		StatePlay::GetInstance()->RemoveTrap(this);


	}
		
}

void BombTrap::UpdateCollideBombTrap(float frameTime, Player* m_Player) {
	
}

int BombTrap::getValueAttack() {
	return m_iAttack;
}