#pragma once
#include"stdafx.h"
#include "Gate.h"
#include "define.h"
#include "ResourceManager.h"
#include "StatePlay.h"
#include "Renderer.h"
#include "InputManager.h"
#include "CollisionManager.h"

#include "SoundEngine.h"

Gate::~Gate() {}

Gate::Gate(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Trap(prefabID, roomID, translationMatrix), m_isCollide(false) {


}

void Gate::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	Player* player = StatePlay::GetInstance()->m_Player;

	if (CheckCollide(player))
		if (InputManager::GetInstance()->keyPressed & KEY_SPACE &&
			player->m_KEY > 0) {
			m_strState = GATE_ACTIVE;
			player->m_KEY--;
			StatePlay::GetInstance()->m_isNextState = true;
		}
}

bool Gate::CheckCollide(Object *object) {
	if (CollisionManager::CheckCollision(this, object)) {
		m_strState = GATE_COLLIDE;
		StatePlay::GetInstance()->m_isGateInstruct = true;
		return true;
	}	
	else {
		m_strState = INIT_ANIM;
		StatePlay::GetInstance()->m_isGateInstruct = false;
		return false;
	}
}