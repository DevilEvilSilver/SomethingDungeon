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
	Prefab* rock1 = GetResource(ROCK_1, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* rock2 = GetResource(ROCK_2, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* grass = GetResource(GRASS, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree1 = GetResource(TREE1, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree2 = GetResource(TREE2, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree3 = GetResource(TREE3, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree4 = GetResource(TREE4, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree5 = GetResource(TREE5, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree6 = GetResource(TREE6, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree7 = GetResource(TREE7, ResourceManager::GetInstance()->m_PrefabList);
	Prefab* tree8 = GetResource(TREE8, ResourceManager::GetInstance()->m_PrefabList);
	if (m_RoomType == NORMAL) {
			
		Matrix translation;
		unsigned int 
			grassNum = 0,
			treeNum1 =1,
			treeNum2 = 0,
			treeNum3= 1,
			treeNum4 =1,
			treeNum5 =1,
			treeNum6 =1,
			treeNum7 = 1,
			treeNum8 = 1,
			rockNum1 = 0,
			rockNum2 = 0,
			enemyNum = 0, 
			hpNum=0,
			mpNum=0,
			bombNum=0;
		unsigned int random = rand() % 100 + 1;

		if (random >= 80)
		{
			enemyNum = 1;
			hpNum = 1;
			mpNum = 1;
			rockNum1 = 1;
			rockNum2 = 0;
			grassNum = 10;
			treeNum2 = 3;
		}
		else if (random >= 50)
		{
			bombNum = 1;
			enemyNum = 2;
			hpNum = 1;
			rockNum2 = 1;
			grassNum = 10;
		}
		else if (random >= 10)
		{
			hpNum = 1;
			enemyNum = 1;
			mpNum = 1;
			rockNum2 = 1;
			grassNum = 10;
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
		while (rockNum1--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - rock1->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - rock1->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* rock1Obj = new Object(ROCK_1, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(rock1Obj);
		}
		while (rockNum2--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - rock2->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - rock2->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* rock1Obj = new Object(ROCK_2, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(rock1Obj);
		}
		while (treeNum1--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree1->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree1->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE1, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum2--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree2->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree2->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE2, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum3--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree3->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree3->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE3, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum4--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree4->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree4->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE4, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum5--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree5->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree5->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE5, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum6--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree6->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree6->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE6, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum7--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree7->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree7->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE7, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
		while (treeNum8--) {

			unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - tree8->m_fWidth);
			unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - tree8->m_fHeight);
			translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
			Object* tree1Obj = new Object(TREE8, m_RoomID, translation);
			StatePlay::GetInstance()->AddDecor(tree1Obj);
		}
	}
}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}