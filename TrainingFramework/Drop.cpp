#pragma once
#include"stdafx.h"
#include"Drop.h"
#include "Renderer.h"

#include "CollisionManager.h"
#include "StatePlay.h"


Drop::Drop()
{
}

Drop::Drop(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

Drop::~Drop() 
{

}

void Drop::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player, frameTime))OnCollision();
}

void Drop::OnCollision()
{
}

