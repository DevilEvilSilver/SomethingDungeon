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
			GenObj(BOMB_TRAP, ((int)random - 20) / 10);
		}
		else if (random >= 0 && random < 20)
		{
			GenObj(SPIKE_TRAP, (int)random / 2);
		}

		

		Prefab* enemyPrefab = GetResource(ENEMY, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		unsigned int enemyNum = 0;

		if (random >= 80) enemyNum = 2;
		else if (random >= 50)	enemyNum = 1;
		else enemyNum = 0;

		while (enemyNum--) {
			
			int rNum = rand() % 100 + 1;

			if (rNum <= 25) AddEnemy(SKELETON);
			else if (rNum <= 50) AddEnemy(WITCH);
			else if (rNum <=75)AddEnemy(BEAR);
			//else if (rNum>=90)AddEnemy(B_ROBOTKNIGHT);

			//Skeleton* enemy = new Skeleton(ENEMY, m_RoomID, translation);

		}
		if (rand()%5<=1)	GenerateDeco();
	}
	else if (m_RoomType == START)
	{
		
		/*Matrix translation;

		unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH - enemyPrefab->m_fWidth);
		unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT - enemyPrefab->m_fHeight);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);*/

		//Witch* enemy = new Witch(WITCH, m_RoomID, translation);
		//RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);
		//Skeleton* enemy = new Skeleton(BEAR, m_RoomID, translation);
		//Goblin* enemy = new Goblin(BEAR, m_RoomID, translation);

		//StatePlay::GetInstance()->AddEnemy(enemy);

		GenerateDeco();
	}
	else if (m_RoomType == END)
	{
		Prefab* enemyPrefab = GetResource(B_ROBOTKNIGHT, ResourceManager::GetInstance()->m_PrefabList);
		Matrix translation;
		translation.SetTranslation(GetPosX() + ROOM_WIDTH/2-enemyPrefab->m_fWidth/2, GetPosY()- ROOM_HEIGHT / 2 + enemyPrefab->m_fHeight/2, 0.0f);

		RobotKnight* enemy = new RobotKnight(B_ROBOTKNIGHT, m_RoomID, translation);

		StatePlay::GetInstance()->AddEnemy(enemy);
	}
}

void Room::GenerateDeco()
{
	int i = rand() % 2 + 1;
	//i = 2;
	while (i>0)
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
			if (rand() % 100 >= 75)
				AddDeco(POLE_1);
			else
				if (rand() % 100 >= 50)
					AddDeco(POLE_2);
				else
					if (rand() % 100 >= 25)
						AddDeco(POLE_3);
					else
						if (rand() % 100 >= 0)
							AddDeco(POLE_4);
		}
		else AddDeco(BROKEN_WALL);


		i--;
	}
}

void Room::AddDeco(std::string prefabName)
{
	Prefab* ObjPrefab = GetResource(prefabName, ResourceManager::GetInstance()->m_PrefabList);
	Vector2 size=Vector2(ObjPrefab->m_fWidth,ObjPrefab->m_fHeight);
	Matrix translation;

	

	bool isDone = false;
	while (isDone==false)
	{
		bool error = false;

		unsigned int randPosX = rand() % (unsigned int)((float)ROOM_WIDTH- size.x);
		unsigned int randPosY = rand() % (unsigned int)((float)ROOM_HEIGHT-size.y-1.0f);
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

		unsigned int randPosX = 1+rand() % (unsigned int)((float)ROOM_WIDTH - size.x-1.0f);
		unsigned int randPosY = 1+rand() % (unsigned int)((float)ROOM_HEIGHT - size.y - 1.0f);
		translation.SetTranslation(GetPosX() + randPosX, GetPosY() - randPosY, 0.0f);

		
		Enemy* result = nullptr;
		if (prefabName==WITCH) 
			result= new Witch(prefabName, m_RoomID, translation);
		else 
			if (prefabName == BEAR)
			result = new Goblin(prefabName, m_RoomID, translation);
		else
			if (prefabName == SKELETON)
				result = new Skeleton(prefabName, m_RoomID, translation);
			else if (prefabName == B_ROBOTKNIGHT)
				result = new RobotKnight(prefabName, m_RoomID, translation);

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
			isDone = true;
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