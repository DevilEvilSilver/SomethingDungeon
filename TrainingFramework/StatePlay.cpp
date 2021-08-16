#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StatePlay.h"
#include "SoundEngine.h"
#include "Object.h"
#include "define.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#define _CRT_SECURE_NO_WARNINGS



template <class T>
T GetRoomByType(RoomType id, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (id == obj->m_RoomType)
			return obj;
	}
	return 0;
}

template <class T>
T GetRoomByID(Vector2 roomID, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (roomID.x == obj->m_RoomID.x && roomID.y == obj->m_RoomID.y)
			return obj;
	}
	return 0;
}

StatePlay::StatePlay(void) {
	this->Init();
}

StatePlay::~StatePlay() {
	for (auto& object : m_ObjectList) {
		delete object;
	}
	m_ObjectList.clear();
	for (auto& object : m_SkillList) {
		delete object;
	}
	m_SkillList.clear();
	for (auto& object : m_RoomList) {
		delete object;
	}
	m_RoomList.clear();
	for (auto& object : m_EnemyList) {
		delete object;
	}
	m_EnemyList.clear();
	for (auto& object : m_GoldList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_GoldList.clear();
	for (auto& object : m_hpPotionList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_hpPotionList.clear();
	for (auto& object : m_mpPotionList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_mpPotionList.clear();
	for (auto& object : m_spikeTrapList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_spikeTrapList.clear();
	for (auto& object : m_bombTrapList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_bombTrapList.clear();

	delete m_Player;
	delete m_Camera;
	delete scoreText;
}

void StatePlay::Init() {
	MapGenerate(MAP_MAX_TUNNEL, TUNNEL_MAX_LENGTH);
	Room *startRoom = GetRoomByType(START, m_RoomList);

	FILE* dataFile;
	dataFile = fopen(FILE_S_PLAY, "r");

	//Player
	fscanf(dataFile, "#PLAYER\n");
	unsigned int id;
	fscanf(dataFile, "ID %d\n", &id);
	char strPrefab[50];
	fscanf(dataFile, "PREFAB %s\n", &strPrefab);
	Matrix translation;
	translation.SetTranslation(startRoom->GetPosX() + ROOM_WIDTH/2.0f, startRoom->GetPosY() - ROOM_HEIGHT/2, 0.0f);
	m_Player = new Player(strPrefab, startRoom->m_RoomID, translation);

	//Camera
	fscanf(dataFile, "#CAMERA\n");
	float fLeft, fRight, fBottom, fTop;
	fscanf(dataFile, "PLANES %f, %f, %f, %f\n", &fLeft, &fRight, &fBottom, &fTop);
	float fNear;
	fscanf(dataFile, "NEAR %f\n", &fNear);
	float fFar;
	fscanf(dataFile, "FAR %f\n", &fFar);
	float fMovingSpeed;
	fscanf(dataFile, "MOVING SPEED %f\n", &fMovingSpeed);
	float fRotationSpeed;
	fscanf(dataFile, "ROTATION SPEED %f\n", &fRotationSpeed);
	m_Camera = new Camera(startRoom->GetPosX() + (startRoom->m_fWidth / 2), startRoom->GetPosY() - (startRoom->m_fHeight / 2), 
		fLeft, fRight, fBottom, fTop, fNear, fFar, fMovingSpeed, fRotationSpeed);
	
	fclose(dataFile);

	scoreText = new Text("Score: 000000", 1, 1, TEXT_COLOR::RED, 20, 20, 1.0f);

}

void StatePlay::MapGenerate(unsigned int maxTunnel, unsigned int maxLength) {
	std::fill_n(*m_Map, sizeof(m_Map) / sizeof(**m_Map), WALL);
	srand(time(NULL));
	unsigned int currPosX = rand() % 30 + 1;
	unsigned int currPosY = rand() % 30 + 1;
	m_Map[currPosX][currPosY] = START;
	Vector2 directions[4] = { Vector2(1, 0), Vector2(0, 1),  Vector2(-1, 0), Vector2(0, -1) };
	unsigned int lastDirection = 0, randDirection = 0;

	while (maxTunnel--) {
		unsigned int tunnelLength = rand() % maxLength + 1;

		do {
			randDirection = rand() % 4;
		} while ((directions[randDirection].x == directions[lastDirection].x &&
			directions[randDirection].y == directions[lastDirection].y) ||
			(directions[randDirection].x == -directions[lastDirection].x &&
				directions[randDirection].y == -directions[lastDirection].y));

		while (tunnelLength--) {
			if ((currPosX == 1) && (directions[randDirection].x == -1) ||
				(currPosX == 30) && (directions[randDirection].x == 1) ||
				(currPosY == 1) && (directions[randDirection].y == -1) ||
				(currPosY == 30) && (directions[randDirection].y == 1)) {
				break;
			}
			else {
				if (m_Map[currPosX][currPosY] != START) 
					m_Map[currPosX][currPosY] = NORMAL;
				currPosX += directions[randDirection].x;
				currPosY += directions[randDirection].y;
				lastDirection = randDirection;
			}
		}
	}
	m_Map[currPosX][currPosY] = END;

	for (unsigned int i = 0; i < 32; i++) {
		for (unsigned int j = 0; j < 32; j++) {
			Matrix translation;
			translation.SetTranslation(i * ROOM_WIDTH, (j + 1) * ROOM_HEIGHT, -1.0f);
			if (m_Map[i][j] == NORMAL) {
				Room *room = new Room(NORMAL_ROOM, Vector2(i, j), translation, NORMAL);
				AddRoom(room);
			}
			else if (m_Map[i][j] == WALL) {
				Room *room = new Room(WALL_ROOM, Vector2(i, j), translation, WALL);
				AddRoom(room);
			}
			else if (m_Map[i][j] == START) {
				Room *room = new Room(NORMAL_ROOM, Vector2(i, j), translation, START);
				AddRoom(room);
			}
			else if (m_Map[i][j] == END) {
				Room *room = new Room(NORMAL_ROOM, Vector2(i, j), translation, END);
				AddRoom(room);
			}
		}
	}
}

void StatePlay::RoomsGenerate() {
	for (auto& obj : m_RoomList) {
		
		obj->RoomGenerate();
	}
}

void StatePlay::Render() {
	GetRenderOrder();

	//RENDER ROOM
	{
		for (auto& obj : m_RoomList) {
			if (CheckInRange(obj->m_RoomID))
				obj->Render(this->m_Camera);
		}
	}

	//RENDER OBJECT
	{
		for (auto& obj : m_ObjectList) {
			if (CheckInRange(obj->m_RoomID))
				obj->Render(this->m_Camera);
		}
	}

	//RENDER TEXT
	{
		Renderer::GetInstance()->DrawText2(scoreText);
		//Renderer::GetInstance()->DrawText2(m_Player->numGoldText);
 		Renderer::GetInstance()->DrawText2(m_Player->numHPText);
	}

	for (auto& obj : m_GoldList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}
	for (auto& obj : m_hpPotionList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}/*
	for (auto& obj : m_mpPotionList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}*/
	for (auto& obj : m_spikeTrapList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}
	for (auto& obj : m_bombTrapList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}

	m_ObjectList.clear();
	for (auto& obj : m_SkillList)
	{
		obj->Render(this->m_Camera);
	}

}
void StatePlay::Update(float frameTime) {


	//check colli with enemy
	for (auto& obj : m_EnemyList) {
		if (CheckInRange(obj->m_RoomID))
			if (CollisionManager::CheckCollision(m_Player, obj, frameTime)) 
			{ 
				obj->isDead = true;
				//release gold - create gold
					obj->createGoldObject();
					AddGold(obj->getGold());
				removeEnemy(obj);
			}	
	}
	
	// check collide  get gold
	for (auto& obj : m_GoldList) {
		if (CheckInRange(obj->m_RoomID))
			if (CollisionManager::CheckCollision(m_Player, obj, frameTime))
				m_Player->UpdateCollideGold(frameTime, obj);
	}

	// check collide  get hp potion
	for (auto& obj : m_hpPotionList) {
		if (CheckInRange(obj->m_RoomID))
			if (CollisionManager::CheckCollision(m_Player, obj, frameTime))
			{
				m_Player->UpdateCollideHP(frameTime, obj);
			}
	}
	for (auto& obj : m_spikeTrapList) {
		if (CheckInRange(obj->m_RoomID))
			if (CollisionManager::CheckCollision(m_Player, obj))
			{
				//m_Player->UpdateCollideSpikeTrap(frameTime, obj);
				obj->UpdateCollideSpikeTrap(frameTime, m_Player);
			}
	}
	for (auto& obj : m_bombTrapList) {
		if (CheckInRange(obj->m_RoomID))
			if (CollisionManager::CheckCollision(m_Player, obj))
			{
				obj->UpdateCollideBombTrap(frameTime, m_Player);
			}
	}
	
	UpdateRoomID();
	m_Player->Update(frameTime);
	
	for (auto& obj : m_EnemyList) {
		if (CheckInRange(obj->m_RoomID))
		{
			obj->Update(frameTime);
		}	
	}
	for (auto& obj : m_SkillList) {
		//if (CheckInRange(obj->m_RoomID))
			obj->Update(frameTime);
	}

	for (auto& obj : m_GoldList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Update(frameTime);
	}

	for (auto& obj : m_hpPotionList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Update(frameTime);
	}

	for (auto& obj : m_spikeTrapList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Update(frameTime);
	}

	for (auto& obj : m_bombTrapList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Update(frameTime);
	}

	UpdateControl(frameTime);

	//follow camera
	m_Camera->SetPosition(Vector3(m_Player->GetPosX(), m_Player->GetPosY(), m_Camera->GetPosition().z));
	m_Camera->Update(frameTime);
}

void StatePlay::UpdateRoomID() {
	if (!CollisionManager::CheckCollision(m_Player, GetRoomByID(m_Player->m_RoomID, m_RoomList))) {
		for (unsigned int i = m_Player->m_RoomID.x - 1; i <= m_Player->m_RoomID.x + 1; i++) {
			if (i > 31)
				continue;

			for (unsigned int j = m_Player->m_RoomID.y - 1; j <= m_Player->m_RoomID.y + 1; j++) {
				if (j > 31)
					continue;
				if (CollisionManager::CheckCollision(m_Player, GetRoomByID(Vector2(i, j), m_RoomList))) {
					m_Player->m_RoomID = Vector2(i, j);
					break;
				}

			}
		}
	}

	for (auto& obj : m_EnemyList) {
		if (CheckInRange(obj->m_RoomID))
		{
			for (unsigned int i = m_Player->m_RoomID.x - 1; i <= m_Player->m_RoomID.x + 1; i++) {
				if (i > 31)
					continue;

				for (unsigned int j = m_Player->m_RoomID.y - 1; j <= m_Player->m_RoomID.y + 1; j++) {
					if (j > 31)
						continue;
					if (CollisionManager::CheckCollision(obj, GetRoomByID(Vector2(i, j), m_RoomList))) {
						obj->m_RoomID = Vector2(i, j);
						break;
					}

				}
			}


		}

	}
}

void StatePlay::UpdateControl(float frameTime)
{
	int newKeyPressed = InputManager::GetInstance()->keyPressed;
	
	//PLAYER
	{
		if ((newKeyPressed & KEY_W))
		{
			m_Player->PlayerMove(m_Player->UP);
		}
		else if (newKeyPressed & KEY_S)
		{
			m_Player->PlayerMove(m_Player->DOWN);
		}

		if ((newKeyPressed & KEY_A))
		{
			m_Player->PlayerMove(m_Player->LEFT);
		}
		else if (newKeyPressed & KEY_D)
		{
			m_Player->PlayerMove(m_Player->RIGHT);
		}

	}
	

	//CAMERA
	{
		if (newKeyPressed & KEY_UP)
		{
			m_Camera->MoveUp(frameTime);
		}
		if (newKeyPressed & KEY_LEFT)
		{
			m_Camera->MoveLeft(frameTime);
		}
		if (newKeyPressed & KEY_DOWN)
		{
			m_Camera->MoveDown(frameTime);
		}
		if (newKeyPressed & KEY_RIGHT)
		{
			m_Camera->MoveRight(frameTime);
		}
	}
	
	//USING SPACE	~	TEST
	m_Player->Attack(1,2);

	{
		if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
		{
			/*m_Player->m_cState = m_Player->CS_DASH;*/
			
			m_Player->Dash(frameTime);
		}
		
		std::string a = "DASH CD: " + std::to_string(m_Player->currDashCD);
		
		scoreText->setText(a);
	}
}

void StatePlay::AddObject(Object *object) {
	m_ObjectList.push_back(object);
}

void StatePlay::AddRoom(Room *room) {
	m_RoomList.push_back(room);
}

void StatePlay::AddEnemy(Enemy *enemy) {
	m_EnemyList.push_back(enemy);
}
void StatePlay::AddSkill(Skill* skill)
{
	m_SkillList.push_back(skill);
}

void StatePlay::AddGold(Gold* gold) {
	m_GoldList.push_back(gold);
}

bool StatePlay::CheckInRange(Vector2 roomID) {

	Vector2 currRoom = m_Player->m_RoomID;
	if (roomID.x < currRoom.x - 1 || roomID.x > currRoom.x + 1 ||
		roomID.y < currRoom.y - 1 || roomID.y > currRoom.y + 1)
		return false;
	else 
		return true;
}

void StatePlay::GetRenderOrder() {
	for (auto a : m_EnemyList) {
		m_ObjectList.push_back(a);
	}
	m_ObjectList.push_back(m_Player);

	std::sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object *a, Object *b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) > (b->GetPosY() - b->m_fHeight));
	});
}


void StatePlay::removeGold(Gold* gold) {
	int id;
	for (int i = 0; i < m_GoldList.size(); i++) {
		if (m_GoldList[i] == gold)  id = i;
	}

	delete m_GoldList[id];
	m_GoldList[id] = m_GoldList[m_GoldList.size() - 1];
	//delete m_GoldList[m_GoldList.size() - 1];
	m_GoldList.resize(m_GoldList.size() -1);
}

void StatePlay::removeEnemy(Enemy* enemy) {
	//enemy->getGold()->m_isDisplay = true;
	int id;
	for (int i = 0; i < m_EnemyList.size(); i++) {
		if (m_EnemyList[i] == enemy)  id = i;
	}

	delete m_EnemyList[id];
	m_EnemyList[id] = m_EnemyList[m_EnemyList.size() - 1];
	m_EnemyList.resize(m_EnemyList.size() - 1);
}

void StatePlay::AddHPPotion(HPPotion* hpPo) {
	m_hpPotionList.push_back(hpPo);
}
void StatePlay::removeHPPotion(HPPotion* hpPo) {
	int id;
	for (int i = 0; i < m_hpPotionList.size(); i++) {
		if (m_hpPotionList[i] == hpPo)  id = i;
	}

	delete m_hpPotionList[id];
	m_hpPotionList[id] = m_hpPotionList[m_hpPotionList.size() - 1];
	m_hpPotionList.resize(m_hpPotionList.size() - 1);
}

void StatePlay::AddMPPotion(MPPotion* mpPo) {
	m_mpPotionList.push_back(mpPo);
}
void StatePlay::removeMPPotion(MPPotion* mpPo) {
	int id;
	for (int i = 0; i < m_mpPotionList.size(); i++) {
		if (m_mpPotionList[i] == mpPo)  id = i;
	}

	delete m_mpPotionList[id];
	m_mpPotionList[id] = m_mpPotionList[m_mpPotionList.size() - 1];
	m_mpPotionList.resize(m_mpPotionList.size() - 1);
}

void StatePlay::AddSpikeTrap(SpikeTrap* trap) {
	m_spikeTrapList.push_back(trap);
}

void StatePlay::AddBombTrap(BombTrap* trap) {
	m_bombTrapList.push_back(trap);
}
void StatePlay::removeBombTrap(BombTrap* trap) {
	int id;
	for (int i = 0; i < m_bombTrapList.size(); i++) {
		if (m_bombTrapList[i] == trap)  id = i;
	}

	delete m_bombTrapList[id];
	m_bombTrapList[id] = m_bombTrapList[m_bombTrapList.size() - 1];
	m_bombTrapList.resize(m_bombTrapList.size() - 1);
}