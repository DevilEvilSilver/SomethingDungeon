#include "stdafx.h"
#include <time.h>
#include "Room.h"
#include "Enemy.h"
#include "Gold.h"
#include "Key.h"
#include "StatePlay.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

#include "Witch.h"
#include "Goblin.h"
#include "Skeleton.h"
#include "CPlant.h"
#include "Frogman.h"
#include "Orcman.h"

#include "RobotKnight.h"

#include "CollisionManager.h"
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
	switch (StatePlay::GetInstance()->m_floorID) {
	case FloorIdentify::FLOOR_1_ID:
		Floor1Generate();
		break;
	case FloorIdentify::FLOOR_2_ID:
		Floor2Generate();
		break;
	case FloorIdentify::FLOOR_3_ID:
		Floor3Generate();
		break;
	case FloorIdentify::FLOOR_BOSS_ID:
		FloorBossGenerate();
		break;
	}
	
}

void Room::Floor1Generate() {
	if (m_RoomType == NORMAL) {
		unsigned int random = rand() % 100 + 1;

		if (random >= 60 && random < 70)
		{
			GenObj(BOMB_TRAP, 1);
		}
		else if (random >= 40 && random < 60)
		{
			GenObj(SPIKE_TRAP, 1);
		}
		else if (random >= 35 && random < 40)
		{
			GenObj(TREASURE, 1);
		}
		else if (random >= 0 && random < 35)
		{
			GenObj(TOWER, 1);
		}

		Prefab* enemyPrefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		unsigned int enemyNum = 0;

		if (random >= 90) enemyNum = 2;
		else if (random >= 70)	enemyNum = 1;
		else enemyNum = 0;


		while (enemyNum--) {

			int rNum = rand() % 100 + 1;

			if (rNum <= 40) AddEnemy(SKELETON);
			else if (rNum <= 55)
			{
				AddEnemy(WITCH);
			}
			else 
			{
				if (rNum <= 70)
				AddEnemy(C_PLANT);
			}

			if (rand() % 10 + 1 <= 1)
				AddEnemy(FROGMAN);

			//Skeleton* enemy = new Skeleton(ENEMY, m_RoomID, translation);

		}
		if (rand() % 5 <= 1)	GenerateDeco();
	}
	else if (m_RoomType == START)
	{

		Matrix translation;
		Prefab* enemyPrefab = GetResource(C_PLANT, ResourceManager::GetInstance()->m_PrefabList);

		unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - enemyPrefab->m_fWidth);
		unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - enemyPrefab->m_fHeight);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);
	}
	else if (m_RoomType == END)
	{
		Prefab *gatePrefab = GetResource(GATE, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - gatePrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + gatePrefab->m_fHeight / 2, 0.0f);
		Gate* gate = new Gate(GATE, m_RoomID, translation);
		StatePlay::GetInstance()->AddTrap(gate);
	}
	else if (m_RoomType == KEY_ROOM) {
		Prefab* keyPrefab = GetResource(KEY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - keyPrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + keyPrefab->m_fHeight / 2, 0.0f);

		Key* key = new Key(KEY, m_RoomID, translation);

		StatePlay::GetInstance()->AddDrop(key);
	}
}

void Room::Floor2Generate() {
	if (m_RoomType == NORMAL) {
		unsigned int random = rand() % 100 + 1;

		if (random >= 60 && random < 70)
		{
			GenObj(BOMB_TRAP, 1);
		}
		else if (random >= 40 && random < 60)
		{
			GenObj(SPIKE_TRAP, 1);
		}
		else if (random >= 35 && random < 40)
		{
			GenObj(TREASURE, 1);
		}
		else if (random >= 0 && random < 35)
		{
			GenObj(TOWER, 1);
		}

		Prefab* enemyPrefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		unsigned int enemyNum = 0;

		if (random >= 90) enemyNum = 2;
		else if (random >= 70)	enemyNum = 1;
		else enemyNum = 0;

		int rNum = rand() % 100 + 1;

		if (rNum <= 40) AddEnemy(SKELETON);
		else if (rNum <= 70)
		{
			AddEnemy(BEAR);
		}
		else
		{
			if (rNum <= 85)
			AddEnemy(WITCH);
		}

		if (rand() % 10 + 1 <= 1)
			AddEnemy(FROGMAN);

		
		if (rand() % 5 <= 2)	GenerateDeco();
		//if (rand() % 5 <= 3) GenerateDeco();
	}
	else if (m_RoomType == START)
	{

		Matrix translation;
		Prefab* enemyPrefab = GetResource(C_PLANT, ResourceManager::GetInstance()->m_PrefabList);

		unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - enemyPrefab->m_fWidth);
		unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - enemyPrefab->m_fHeight);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);

		//Witch* enemy = new Witch(WITCH, m_RoomID, translation);
		//RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);
		//Skeleton* enemy = new Skeleton(BEAR, m_RoomID, translation);
		//Goblin* enemy = new Goblin(C_PLANT, m_RoomID, translation);
		//CPlant* enemy = new CPlant(C_PLANT, m_RoomID, translation);
		//Orcman* enemy = new Orcman(ORCMAN, m_RoomID, translation);
		//StatePlay::GetInstance()->AddEnemy(enemy);

		//GenerateDeco();
	}
	else if (m_RoomType == END)
	{
		Prefab *gatePrefab = GetResource(GATE, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - gatePrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + gatePrefab->m_fHeight / 2, 0.0f);
		Gate* gate = new Gate(GATE, m_RoomID, translation);
		StatePlay::GetInstance()->AddTrap(gate);

		//Prefab* enemyPrefab = GetResource(B_ROBOTKNIGHT, ResourceManager::GetInstance()->m_PrefabList);
		//translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - enemyPrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + enemyPrefab->m_fHeight / 2, 0.0f);
		//RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);
		//StatePlay::GetInstance()->AddEnemy(enemy);
	}
	else if (m_RoomType == KEY_ROOM) {
		Prefab* keyPrefab = GetResource(KEY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - keyPrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + keyPrefab->m_fHeight / 2, 0.0f);

		Key* key = new Key(KEY, m_RoomID, translation);

		StatePlay::GetInstance()->AddDrop(key);
	}
}

void Room::Floor3Generate() {
	if (m_RoomType == NORMAL) {
		unsigned int random = rand() % 100 + 1;

		if (random >= 60 && random < 70)
		{
			GenObj(BOMB_TRAP, 1);
		}
		else if (random >= 40 && random < 60)
		{
			GenObj(SPIKE_TRAP, 1);
		}
		else if (random >= 35 && random < 40)
		{
			GenObj(TREASURE, 1);
		}
		else if (random >= 0 && random < 35)
		{
			GenObj(TOWER, 1);
		}

		Prefab* enemyPrefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		unsigned int enemyNum = 0;

		if (random >= 90) enemyNum = 3;
		else if (random >= 70)	enemyNum = 1;
		else enemyNum = 0;



		while (enemyNum--) {

			int rNum = rand() % 100 + 1;

			if (rNum <= 40) AddEnemy(SKELETON);
			else if (rNum <= 70)
			{
				if (rand() % 10 + 1 <= 6)
					AddEnemy(WITCH);
				else AddEnemy(C_PLANT);
			}
			else
			{
				if (rNum <= 85) AddEnemy(BEAR);
				else AddEnemy(ORCMAN);
			}

			if (rand() % 10 + 1 <= 1)
				AddEnemy(FROGMAN);

			//Skeleton* enemy = new Skeleton(ENEMY, m_RoomID, translation);

		}
		if (rand() % 5 <= 2)	GenerateDeco();
		//if (rand() % 5 <= 1)	GenerateDeco();
	}
	else if (m_RoomType == START)
	{

		Matrix translation;
		Prefab* enemyPrefab = GetResource(C_PLANT, ResourceManager::GetInstance()->m_PrefabList);

		unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - enemyPrefab->m_fWidth);
		unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - enemyPrefab->m_fHeight);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);

		//Witch* enemy = new Witch(WITCH, m_RoomID, translation);
		//RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);
		//Skeleton* enemy = new Skeleton(BEAR, m_RoomID, translation);
		//Goblin* enemy = new Goblin(C_PLANT, m_RoomID, translation);
		//CPlant* enemy = new CPlant(C_PLANT, m_RoomID, translation);
		//Orcman* enemy = new Orcman(ORCMAN, m_RoomID, translation);
		//StatePlay::GetInstance()->AddEnemy(enemy);

		//GenerateDeco();
	}
	else if (m_RoomType == END)
	{
		Prefab *gatePrefab = GetResource(GATE, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - gatePrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + gatePrefab->m_fHeight / 2, 0.0f);
		Gate* gate = new Gate(GATE, m_RoomID, translation);
		StatePlay::GetInstance()->AddTrap(gate);

		//Prefab* enemyPrefab = GetResource(B_ROBOTKNIGHT, ResourceManager::GetInstance()->m_PrefabList);
		//translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - enemyPrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + enemyPrefab->m_fHeight / 2, 0.0f);
		//RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);
		//StatePlay::GetInstance()->AddEnemy(enemy);
	}
	else if (m_RoomType == KEY_ROOM) {
		Prefab* keyPrefab = GetResource(KEY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - keyPrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + keyPrefab->m_fHeight / 2, 0.0f);

		Key* key = new Key(KEY, m_RoomID, translation);

		StatePlay::GetInstance()->AddDrop(key);
	}
}

void Room::FloorBossGenerate() {
	if (m_RoomType == NORMAL) {
		unsigned int random = rand() % 100 + 1;

		if (random > 50)	GenerateDeco();
	}
	else if (m_RoomType == END)
	{
		Prefab *gatePrefab = GetResource(GATE, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - gatePrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + gatePrefab->m_fHeight / 2, 0.0f);
		Gate* gate = new Gate(GATE, m_RoomID, translation);
		StatePlay::GetInstance()->AddTrap(gate);

		Prefab* enemyPrefab = GetResource(B_ROBOTKNIGHT, ResourceManager::GetInstance()->m_PrefabList);
		translation.SetTranslation(GetPosX() + ROOM_WIDTH / 2 - enemyPrefab->m_fWidth / 2, GetPosY() - ROOM_HEIGHT / 2 + enemyPrefab->m_fHeight / 2, 0.0f);
		RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);

		StatePlay::GetInstance()->AddEnemy(enemy);
	}
}

void Room::GenerateDeco()
{
	int i = rand() % 2 + 1;
	//i = 2;

	switch (StatePlay::GetInstance()->m_floorID) {
	case FloorIdentify::FLOOR_2_ID:
		//i *= 2;
		while (i > 0)
		{
			int randomNum = rand() % 100 + 1;

			if (randomNum >= 80)
			{
				int randomNum = rand() % 100 + 1;

				if (randomNum >= 80)
				{
					if (rand() % 100 >= 60)
						AddDeco(DOUBLE_BARRELS);
					else
						AddDeco(TRIO_BARRELS);
				}
				else if (randomNum >= 15)
				{
					randomNum = rand() % 100 + 1;
					if (rand() % 100 >= 75)
						AddDeco(POLE_1);
					else
						if (randomNum >= 50)
							AddDeco(POLE_2);
						else
							if (randomNum >= 25)
								AddDeco(POLE_3);
							else
								if (randomNum >= 0)
									AddDeco(POLE_4);
				}
				else AddDeco(BROKEN_WALL);


				i--;
			}
			break;
		}
		break;
	case FloorIdentify::FLOOR_1_ID:
		while (i > 0)
		{
			int randomNum = rand() % 100 + 1;

			if (randomNum >= 80)
			{
				randomNum = rand() % 100 + 1;
				if (randomNum >= 66)
					AddDeco(F2_TOMB_1);
				else
					if (randomNum >= 33)
						AddDeco(F2_TOMB_2);
					else
						if (randomNum >= 0)
							AddDeco(F2_WELL);
			}
			else if (randomNum >= 10)
			{
				randomNum = rand() % 100 + 1;
				if (randomNum >= 66)
					AddDeco(F2_TREE_1);
				else
					if (randomNum >= 33)
						AddDeco(F2_TREE_2);
					else
						if (randomNum >= 0)
							AddDeco(F2_TREE_3);
			}
			else AddDeco(F2_ROCK);

			if (rand() % 10 <= 5)
			{
				randomNum = rand() % 100 + 1;
				if (randomNum >= 75)
					AddDeco(F2_POLE_1);
				else
					if (randomNum >= 50)
						AddDeco(F2_POLE_2);
					else
						if (randomNum >= 25)
							AddDeco(F2_POLE_3);
						else
							if (randomNum >= 0)
								AddDeco(F2_POLE_4);
			}

			i--;
		}
		break;
	case FloorIdentify::FLOOR_3_ID:
		while (i > 0)
		{
			int randomNum = rand() % 100 + 1;

			if (randomNum >= 80)
			{
				if (rand() % 100 >= 60)
					AddDeco(BOX);
				else
					AddDeco(BROKEN_COFFIN);
			}
			else if (randomNum >= 15)
			{
				if (rand() % 100 >= 75)
					AddDeco(BROKEN_COFFIN_2);
				else
					if (rand() % 100 >= 50)
						AddDeco(NORMAL_VASE);
					else
						if (rand() % 100 >= 25)
							AddDeco(BROKEN_VASE);
						else
							if (rand() % 100 >= 0)
								AddDeco(FLOOR3_POLE_1);
			}
			else AddDeco(FLORR3_POLE_2);


			i--;
		}
		break;
		i--;
	}
}

void Room::AddDeco(std::string prefabName)
{
	Prefab* ObjPrefab = GetResource(prefabName, ResourceManager::GetInstance()->m_PrefabList);
	Vector2 size=Vector2(ObjPrefab->m_fWidth,ObjPrefab->m_fHeight);
	Vector2 delta = Vector2(ObjPrefab->m_fDeltaX, ObjPrefab->m_fDeltaY);
	Matrix translation;

	

	bool isDone = false;
	while (isDone==false)
	{
		bool error = false;

		unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - size.x);
		unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - size.y - 1.0f);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);

		Decorations* result = new Decorations(prefabName, m_RoomID, translation);

		if (error == false)
		for (auto& obj : StatePlay::GetInstance()->m_EnemyList) {
			if (obj->m_RoomID.x==m_RoomID.x&& obj->m_RoomID.y == m_RoomID.y)
				if (CollisionManager::CheckCollision(result, obj,0.0f) == true)
				{
					error = true;
				}
		}


		if (error==false)
		for (auto& obj : StatePlay::GetInstance()->m_DropList) {
			if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
				if (CollisionManager::CheckCollision(result, obj,0.0f) == true)
				{
					error = true;
				}
		}

		if (error == false)
		for (auto& obj : StatePlay::GetInstance()->m_TrapList) {
			if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
				if (CollisionManager::CheckCollision(result, obj,0.0f) == true)
				{
					error = true;
				}
		}
		
		if (error == false)
		for (auto& obj : StatePlay::GetInstance()->m_DecorationList) {
			if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
				if (CollisionManager::CheckCollision(result, obj,0.0f) == true)
				{
					error = true;
				}
		}

		if (error == false)
			for (auto& obj : StatePlay::GetInstance()->m_RoomList) {
				if (obj->m_RoomType==WALL)
					if (CollisionManager::CheckCollision(result, obj, 0.0f) == true)
					{
						error = true;
					}
			}
		

		if (error == false)
		{
			isDone = true;
			StatePlay::GetInstance()->AddDecoration(result);
		}
		else {
			//printf("hey1\n");
			delete result;
			isDone = true;
		}
		
			
	}

}

void Room::AddEnemy(std::string prefabName)
{
	Prefab* ObjPrefab = GetResource(prefabName, ResourceManager::GetInstance()->m_PrefabList);
	Vector2 size = Vector2(ObjPrefab->m_fWidth, ObjPrefab->m_fHeight);
	Matrix translation;



	bool isDone = false;
	while (isDone == false)
	{
		bool error = false;

		unsigned int randPosX = 2+rand() % (unsigned int)((float)ROOM_WIDTH - size.x-2.0f);
		unsigned int randPosY = 2+rand() % (unsigned int)((float)ROOM_HEIGHT - size.y - 2.0f);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);

		
		Enemy* result = nullptr;
		if (prefabName == WITCH)
			result = new Witch(prefabName, m_RoomID, translation);
		else
			if (prefabName == BEAR)
				result = new Goblin(BEAR, m_RoomID, translation);
		else
			if (prefabName == SKELETON)
				result = new Skeleton(prefabName, m_RoomID, translation);
		else
			if (prefabName == C_PLANT)
				result = new CPlant(prefabName, m_RoomID, translation);
		else
			if (prefabName == FROGMAN)
				result = new Frogman(prefabName, m_RoomID, translation);
		else
			if (prefabName == ORCMAN)
				result = new Orcman(prefabName, m_RoomID, translation);

		if (error == false)
			for (auto& obj : StatePlay::GetInstance()->m_EnemyList) {
				if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
					if (CollisionManager::CheckCollision(result, obj, 0.0f) == true)
					{
						error = true;
					}
			}


		if (error == false)
			for (auto& obj : StatePlay::GetInstance()->m_DropList) {
				if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
					if (CollisionManager::CheckCollision(result, obj, 0.0f) == true)
					{
						error = true;
					}
			}

		if (error == false)
			for (auto& obj : StatePlay::GetInstance()->m_TrapList) {
				if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
					if (CollisionManager::CheckCollision(result, obj, 0.0f) == true)
					{
						error = true;
					}
			}

		if (error == false)
			for (auto& obj : StatePlay::GetInstance()->m_DecorationList) {
				if (obj->m_RoomID.x == m_RoomID.x && obj->m_RoomID.y == m_RoomID.y)
					if (CollisionManager::CheckCollision(result, obj, 0.0f) == true)
					{
						error = true;
					}
			}


		if (error == false)
		{
			isDone = true;
			StatePlay::GetInstance()->AddEnemy(result);
		}
		else {
			//printf("hey1\n");
			delete result;
			//isDone = true;
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
	unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - 2*ObjPrefab->m_fHeight) - (unsigned int)ObjPrefab->m_fHeight;
	Matrix translation;
	
	unsigned int random = rand() % 100 + 1;
	while (num--)
	{
		unsigned int random = rand() % 100 + 1;
		if (random > 50)
		{
			if ((randPosX + 1) <= (ROOM_WIDTH - ObjPrefab->m_fWidth) && (randPosX + 1) >= (ObjPrefab->m_fWidth))
				randPosX++;
		}
		else
		{
			if ((randPosY + 1) <= (+ROOM_HEIGHT - ObjPrefab->m_fHeight) && (randPosY + 1) >= (ObjPrefab->m_fHeight))
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
			//BombTrap* bombTrap = new BombTrap(BOMB_TRAP, m_RoomID, translation);
			//StatePlay::GetInstance()->AddTrap(bombTrap);
		}
		else if (prefabId == ENEMY)
		{
			Enemy* enemy = new Enemy(ENEMY, m_RoomID, translation);
			StatePlay::GetInstance()->AddEnemy(enemy);
		}
		else if (prefabId == TREASURE) {
			//Matrix translation2;
			//translation2.SetTranslation(GetPosX() + randPosX + 4, GetPosY() - randPosY + 3, 0.0f);
			Chest* chest = new Chest(TREASURE, m_RoomID, translation, 5);
			StatePlay::GetInstance()->AddTrap(chest);
		}
		else if (prefabId == TOWER) {
			ArrowTower* tower = new ArrowTower(TOWER, m_RoomID, translation);
			/*if (rand()%2==0) tower->m_isFacingLeft = false;
			else tower->m_isFacingLeft = true;*/

			
			StatePlay::GetInstance()->AddTrap(tower);

			if (tower->GetCenterPos().x > this->GetCenterPos().x) tower->m_isFacingLeft = true;
			else tower->m_isFacingLeft = false;
		}
		

		
	}

}