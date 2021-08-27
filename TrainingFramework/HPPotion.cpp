#pragma once
#include"stdafx.h"
#include "HPPotion.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "StatePlay.h"

#include "SoundEngine.h"
HPPotion::~HPPotion() 
{
}

void HPPotion::OnCollision()
{
	Player* player = StatePlay::GetInstance()->m_Player;

	player->m_currHP = (player->m_currHP + this->getValue());
	if (player->m_currHP > player->m_maxHP) player->m_currHP = player->m_maxHP;
	SoundEngine::GetInstance()->Play(REGEN, 1.0f, 1.0f, false);
	isPicked = true;
}

HPPotion::HPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = HP_POTION;
	
}



int HPPotion::getValue() {
	return m_iValue;
}