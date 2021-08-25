#pragma once
#include"stdafx.h"
#include "ArrowTower.h"
#include "define.h"
#include "ResourceManager.h"
#include "StatePlay.h"
#include "Renderer.h"
#include "Arrow.h"
#include "CollisionManager.h"

#include "SoundEngine.h"

ArrowTower::~ArrowTower() {}

ArrowTower::ArrowTower(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = ARROW_TOWER;
}



void ArrowTower::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;

	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();

	float totalCD = 1.0f;
	if (currCD <= 0.0f) {
		currCD = totalCD;
		createArrow();
	}
	else {
		currCD -= frameTime;
	}
	
}



void ArrowTower::createArrow() {
	Matrix translation2;
	translation2.SetTranslation(GetPosX(), GetPosY(), 0.0f);
	Arrow* arrow = new Arrow("arrow", m_RoomID, translation2);
	StatePlay::GetInstance()->AddTrap(arrow);
}