#include "stdafx.h"
#include <time.h>
#include "Room.h"
#include "Enemy.h"
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
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - m_fHeight + randPosY, 0.0f);
			Enemy *enemy = new Enemy(ENEMY, m_RoomID, translation);
			SceneManager::GetInstance()->AddEnemy(enemy);
		}
	}
}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}