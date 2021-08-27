#pragma once
#include"stdafx.h"
#include"Chest.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "StatePlay.h"
#include "CollisionManager.h"
#include "SoundEngine.h"

Chest::~Chest() {}

Chest::Chest(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value)
	: Trap(prefabID, roomID, translationMatrix) {
	m_strState = CHEST;
}

void Chest::Update(float frameTime) {
	OnCollision();
}

void Chest::OnCollision()
{
	for (auto& skill : StatePlay::GetInstance()->m_InRangeSkill) {
		if (skill->m_isPlayer && CollisionManager::CheckCollision(this, skill)) {
			createDrop();
			isExploded = true;
			SoundEngine::GetInstance()->Play(COIN, 1.0f, 1.0f, false);
			break;
		}
	}
}


void Chest::createDrop()
{
	unsigned int random = rand() % 100 + 1;

	Matrix translation;
	translation.SetTranslation(GetPosX(), GetPosY(), 0.0f);


	if (random >= 75)
	{
		HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(hp);
	}
	else if (random >= 50)
	{
		MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(mp);
	}
	else
	{
		Gold* gold = new Gold(GOLD, m_RoomID, translation, 20, false);
		StatePlay::GetInstance()->AddDrop(gold);
	}

}

