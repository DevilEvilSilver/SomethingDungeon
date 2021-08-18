#pragma once
#include"stdafx.h"
#include "Gold.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "StatePlay.h"

#include "SoundEngine.h"
Gold::~Gold() {}

void Gold::OnCollision()
{
	Player* player = StatePlay::GetInstance()->m_Player;

	player->m_GOLD+= this->getValue();
	player->numGoldText->setText("Gold: " + std::to_string(player->m_GOLD));

	SoundEngine::GetInstance()->Play(COIN, 1.0f, 1.0f, false);
	StatePlay::GetInstance()->RemoveDrop(this);

	
}

Gold::Gold(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value, bool isDisplay)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = GOLD_SPIN;
	m_iValue = value;
	//m_isDisplay = isDisplay;
}





int Gold::getValue() {
	return m_iValue;
}