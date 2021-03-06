#include"stdafx.h"
#include "MPPotion.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "StatePlay.h"

#include "SoundEngine.h"
MPPotion::~MPPotion()
{
}

void MPPotion::OnCollision()
{
	Player* player = StatePlay::GetInstance()->m_Player;

	//player->m_currMP = (player->m_currMP + this->getValue());
	player->m_currMP += player->m_maxMP * 0.33;
	if (player->m_currMP>player->m_maxMP) player->m_currMP=player->m_maxMP;

	SoundEngine::GetInstance()->Play(REGEN, 1.0f, 1.0f, false);
	isPicked = true;
}

MPPotion::MPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = MP_POTION;
}



int MPPotion::getValue() {
	return m_iValue;
}