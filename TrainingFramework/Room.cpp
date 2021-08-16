#include "stdafx.h"
#include <time.h>
#include "Room.h"
#include "Enemy.h"
#include "Gold.h"
#include "StatePlay.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

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
	Prefab* enemyPrefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* hpPrefab = GetResource(HP_PO, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* mpPrefab = GetResource(MP_PO, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* bombPrefab = GetResource(BOMB_TRAP, ResourceManager::GetInstance()->m_PrefabList);

	if (m_RoomType == NORMAL) {
			
		Matrix translation;
		unsigned int 
			enemyNum = 0, 
			hpNum=0,
			mpNum=0,
			bombNum=0;
		unsigned int random = rand() % 100 + 1;

		if (random >= 80)
		{
			enemyNum = 3;
			hpNum = 1;
			mpNum = 1;
		}
		else if (random >= 50)
		{
			bombNum = 1;
			enemyNum = 2;
			hpNum = 1;
		}
		else if (random >= 10)
		{
			hpNum = 1;
			enemyNum = 1;
			mpNum = 1;
		}
			
		while (enemyNum--) {
			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - enemyPrefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - enemyPrefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Enemy *enemy = new Enemy(ENEMY, m_RoomID, translation);
			StatePlay::GetInstance()->AddEnemy(enemy);
		}


		while (hpNum--) {
			
			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - hpPrefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - hpPrefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation);
			StatePlay::GetInstance()->AddDrop(hp);

		}

		while (mpNum--) {
			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - mpPrefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - mpPrefab->m_fHeight);
			MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation);
			StatePlay::GetInstance()->AddDrop(mp);

		}

		while (bombNum--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - bombPrefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - bombPrefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			BombTrap* bomb = new BombTrap(BOMB_TRAP, m_RoomID, translation);
			StatePlay::GetInstance()->AddTrap(bomb);
		}
	}
}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}