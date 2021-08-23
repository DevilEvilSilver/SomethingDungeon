#include "stdafx.h"
#include <time.h>
#include "Room.h"
#include "Enemy.h"
#include "Gold.h"
#include "StatePlay.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

#include "Witch.h"
#include "Goblin.h"
#include "Skeleton.h"

template <class T>
T GetResource(std::string id, std::vector<T> objList) {
	for (auto& obj : objList) {
		if (!strcmp(id.c_str(), obj->m_strResourceID.c_str()))
			return obj;
	}
	return 0;
}

Room::Room() {}

Room::Room(std::string prefabID, Vector2 roomID, Matrix translationMatrix, RoomType roomType)
	: Object(prefabID, roomID, translationMatrix), m_RoomType(roomType) {

}

Room::~Room() {

}

void Room::RoomGenerate() {

	if (m_RoomType == NORMAL) {
		unsigned int random = rand() % 100 + 1;

		if (random >= 60 && random < 70)
		{
			GenObj(HP_PO, 1);
		}
		else if (random >= 40 && random < 60)
		{
			GenObj(MP_PO, 1);
		}
		else if (random >= 20 && random < 40)
		{
			GenObj(BOMB_TRAP, ((int)random-20)/10);
		}
		else if (random >= 0 && random < 20)
		{
			GenObj(SPIKE_TRAP, (int)random/2);
		}

		Prefab* enemyPrefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		unsigned int enemyNum = 0;

		if (random >= 80) enemyNum = 2;
		else if (random >= 50)	enemyNum = 1;
		else enemyNum = 0;

		while (enemyNum--) {
			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - enemyPrefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - enemyPrefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			//Enemy* enemy = new Enemy(ENEMY, m_RoomID, translation);
			Witch* enemy = new Witch(ENEMY, m_RoomID, translation);
			
			//Skeleton* enemy = new Skeleton(ENEMY, m_RoomID, translation);

			StatePlay::GetInstance()->AddEnemy(enemy);
		}
	}
}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void Room::GenObj(std::string prefabId, int num)
{
	Prefab* ObjPrefab = GetResource(prefabId, ResourceManager::GetInstance()->m_PrefabList);
	unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - 2*ObjPrefab->m_fWidth)+ (unsigned int)ObjPrefab->m_fWidth;
	unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - 2*ObjPrefab->m_fHeight) + (unsigned int)ObjPrefab->m_fHeight;
	Matrix translation;
	
	unsigned int random = rand() % 100 + 1;
	while (num--)
	{
		unsigned int random = rand() % 100 + 1;
		if (random > 50)
		{
			if ((randPosX + 1) <= ( ROOM_WIDTH - ObjPrefab->m_fWidth) && (randPosX + 1) >= ( ObjPrefab->m_fWidth))
				randPosX++;
		}
		else
		{
			if ((randPosY + 1) <= (+ ROOM_HEIGHT - ObjPrefab->m_fHeight) && (randPosY + 1) >= (  ObjPrefab->m_fHeight))
				randPosY++;
		}

		
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
		if (prefabId == SPIKE_TRAP)
		{
			SpikeTrap* spikeTrap = new SpikeTrap(SPIKE_TRAP, m_RoomID, translation);
			StatePlay::GetInstance()->AddTrap(spikeTrap);
		}
		else if (prefabId == BOMB_TRAP)
		{
			BombTrap* bombTrap = new BombTrap(BOMB_TRAP, m_RoomID, translation);
			StatePlay::GetInstance()->AddTrap(bombTrap);
		}
		else if (prefabId == ENEMY)
		{
			Enemy* enemy = new Enemy(ENEMY, m_RoomID, translation);
			StatePlay::GetInstance()->AddEnemy(enemy);
		}
		else if (prefabId == HP_PO)
		{
			HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation);
			StatePlay::GetInstance()->AddDrop(hp);
		}
		else if (prefabId == MP_PO)
		{
			MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation);
			StatePlay::GetInstance()->AddDrop(mp);
		}
	}

	//
}