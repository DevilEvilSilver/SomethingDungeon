#include"stdafx.h"
#include "MPPotion.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "StatePlay.h"

MPPotion::~MPPotion()
{
}

void MPPotion::OnCollision()
{
	Player* player = StatePlay::GetInstance()->m_Player;

	player->m_currMP = (player->m_currMP + this->getValue());
	if (player->m_currMP>player->m_maxMP) player->m_currMP=player->m_maxMP;
	player->numMPText->setText("MP: " + std::to_string(player->m_currMP));

	StatePlay::GetInstance()->RemoveDrop(this);
}

MPPotion::MPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = MP_POTION;
}



int MPPotion::getValue() {
	return m_iValue;
}