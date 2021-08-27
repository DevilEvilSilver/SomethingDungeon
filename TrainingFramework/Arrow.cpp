#pragma once
#include "stdafx.h"
#include "Arrow.h"
#include "StatePlay.h"
#include "CollisionManager.h"
#include "Room.h"
#include "define.h"


Arrow::~Arrow()
{
}

Arrow::Arrow(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = "ar_static";
	//isCollide = false;
	if (m_isFacingLeft = true)
	{
		dir = -1;
	}
	else dir = 1;

		
	m_iAttack = 5;
}

void Arrow::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	if (dir == -1) m_isFacingLeft = true;
	else m_isFacingLeft = false;
	SetPosX(m_WorldMatrix.m[3][0] + 10 * frameTime*dir);
	//m_WorldMatrix.m[3][0] += 10* frameTime;

	std::vector<Room*> roomList = StatePlay::GetInstance()->m_InRangeRoom;
	for (auto& obj : roomList) {
		if (obj->m_RoomType == WALL)
		{
			if (CollisionManager::CheckCollision(this, obj))
			{
				isExploded = true; 
				break;
			}
		}
	}

	if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player)) {
		isExploded = true;
		StatePlay::GetInstance()->m_Player->UpdateGotHit(m_iAttack, true, Vector2(0.0f, 0.0f), frameTime);
	}

	std::vector<Enemy*> enemyList = StatePlay::GetInstance()->m_InRangeEnemy;
	for (auto& enemy : enemyList) {
		if (CollisionManager::CheckCollision(this, enemy)) {
			isExploded = true;
			enemy->UpdateGotHit(m_iAttack, true, Vector2(0.0f, 0.0f), frameTime);
		}
	}
}

