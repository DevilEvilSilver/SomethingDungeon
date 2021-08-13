#include "stdafx.h"
#include <time.h>
#include "Room.h"
#include "Enemy.h"
#include "Gold.h"
#include "SceneManager.h"
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
		unsigned int iLoop = 0;
		if (random >= 80)
			iLoop = 3;
		else if (random >= 50)
			iLoop = 2;
		else if (random >= 10)
			iLoop = 1;

		while (iLoop--) {
			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - prefab->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - prefab->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - m_fHeight + randPosY, 0.0f);
			Enemy *enemy = new Enemy(ENEMY, m_RoomID, translation);
			SceneManager::GetInstance()->AddEnemy(enemy);

			//tien add
			/*translation.SetTranslation(GetPosX() + randPosX +2, GetPosY() - m_fHeight + randPosY +2, 0.0f);
			Gold* gold = new Gold(GOLD, m_RoomID, translation, rand()%4 +1, false);
			enemy->setGold(gold);
			SceneManager::GetInstance()->AddGold(gold)*/; 

			translation.SetTranslation(GetPosX() + randPosX + 4, GetPosY() - m_fHeight + randPosY + 4, 0.0f);
			HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation, rand() % 50 + 1);
			SceneManager::GetInstance()->AddHPPotion(hp);

			translation.SetTranslation(GetPosX() + randPosX + 3, GetPosY() - m_fHeight + randPosY + 3, 0.0f);
			MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation, rand() % 50 + 1);
			SceneManager::GetInstance()->AddMPPotion(mp);
		}
	}
}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}