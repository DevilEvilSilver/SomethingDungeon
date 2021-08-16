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
	Prefab* prefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);

	if (m_RoomType == NORMAL) {
		unsigned int random = rand() % 100 + 1;
		Matrix translation;
		unsigned int enemyNum = 0;
		if (random >= 80)
			enemyNum = 3;
		else if (random >= 50)
			enemyNum = 2;
		else if (random >= 10)
			enemyNum = 1;

		while (enemyNum--) {
			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - prefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - prefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Enemy *enemy = new Enemy(ENEMY, m_RoomID, translation);
			StatePlay::GetInstance()->AddEnemy(enemy);

			//tien add
			/*translation.SetTranslation(GetPosX() + randPosX +2, GetPosY() - m_fHeight + randPosY +2, 0.0f);
			Gold* gold = new Gold(GOLD, m_RoomID, translation, rand()%4 +1, false);
			enemy->setGold(gold);
			StatePlay::GetInstance()->AddGold(gold)*/; 

			randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - prefab->m_fWidth);
			randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - prefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation, rand() % 50 + 1);
			StatePlay::GetInstance()->AddHPPotion(hp);

			randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - prefab->m_fWidth);
			randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - prefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() -  randPosY, 0.0f);
			MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation, rand() % 50 + 1);
			StatePlay::GetInstance()->AddMPPotion(mp);

			randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - prefab->m_fWidth);
			randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - prefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			BombTrap* bomb = new BombTrap(BOMB_TRAP, m_RoomID, translation, 2);
			StatePlay::GetInstance()->AddBombTrap(bomb);


		}
	}
}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}