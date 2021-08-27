#pragma once
#include"stdafx.h"
#include "Key.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "StatePlay.h"

#include "SoundEngine.h"
Key::~Key() {}

void Key::OnCollision()
{
	Player* player = StatePlay::GetInstance()->m_Player;

	player->m_KEY++;

	SoundEngine::GetInstance()->Play(COIN, 1.0f, 1.0f, false);
	isPicked = true;


}

Key::Key(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = KEY_SPIN;
	//m_isDisplay = isDisplay;
}