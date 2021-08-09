#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "SceneManager.h"
#include "SoundEngine.h"
#include "Object.h"
#include "define.h"
#include "InputManager.h"
#include "StateManager.h"
#include "PhysicEngine.h"
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

SceneManager::SceneManager(void) {
	this->Init();
}

SceneManager::~SceneManager() {
	for (auto& object : m_ObjectList) {
		delete object;
	}
	m_ObjectList.clear();
	for (auto& object : m_RoomList) {
		delete object;
	}
	m_RoomList.clear();
	for (auto& object : m_EnemyList) {
		delete object;
	}
	m_EnemyList.clear();

	delete m_Player;
	delete m_Camera;
}

void SceneManager::Init() {
	MapGenerate(MAP_MAX_TUNNEL, TUNNEL_MAX_LENGTH);
	Room *startRoom = GetRoomByType(START, m_RoomList);

	FILE* dataFile;
	dataFile = fopen(FILE_SM, "r");

	//Player
	fscanf(dataFile, "#PLAYER\n");
	unsigned int id;
	fscanf(dataFile, "ID %d\n", &id);
	char strPrefab[50];
	fscanf(dataFile, "PREFAB %s\n", &strPrefab);
	Matrix translation;
	translation.SetTranslation(startRoom->GetPosX() + PLAYER_START_POSX, startRoom->GetPosY() - startRoom->m_fHeight + PLAYER_START_POSY, 0.0f);
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
}

void SceneManager::MapGenerate(unsigned int maxTunnel, unsigned int maxLength) {
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

void SceneManager::RoomsGenerate() {
	for (auto& obj : m_RoomList) {
		obj->RoomGenerate();
	}
}

void SceneManager::Render() {
	//GetRenderOrder();

	for (auto& obj : m_RoomList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}

	m_Player->Render(this->m_Camera);

	for (auto& obj : m_EnemyList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Render(this->m_Camera);
	}
}

void SceneManager::Update(float frameTime) {
	UpdateRoomID();

	m_Camera->Update(frameTime);
	m_Player->Update(frameTime);

	for (auto& obj : m_EnemyList) {
		if (CheckInRange(obj->m_RoomID))
			obj->Update(frameTime);
	}

	Control(frameTime);
}

void SceneManager::UpdateRoomID() {
	if (!PhysicEngine::GetInstance()->CheckCollision(m_Player, GetRoomByID(m_Player->m_RoomID, m_RoomList))) {
		for (unsigned int i = m_Player->m_RoomID.x - 1; i <= m_Player->m_RoomID.x + 1; i++) {
			if (i > 31)
				continue;
			for (unsigned int j = m_Player->m_RoomID.y - 1; j <= m_Player->m_RoomID.y + 1; j++) {
				if (j > 31)
					continue;
				if (PhysicEngine::GetInstance()->CheckCollision(m_Player, GetRoomByID(Vector2(i, j), m_RoomList))) {
					m_Player->m_RoomID = Vector2(i, j);
				}
			}
		}
	}
}

void SceneManager::UpdateControl(float frameTime)
{
	
	float fSpeed = 20.0f;
	int newKeyPressed = InputManager::GetInstance()->keyPressed;
	if ((newKeyPressed & KEY_W))
	{
		m_Player->SetVelocityY(fSpeed);
	}
	else if (newKeyPressed & KEY_S )
	{
		m_Player->SetVelocityY(-fSpeed);
	}
	else
		m_Player->SetVelocityY(0);

	if ((newKeyPressed & KEY_A))
	{
		m_Player->SetVelocityX(-fSpeed);
	}
	else if (newKeyPressed & KEY_D)
	{
		m_Player->SetVelocityX(fSpeed);
	}
	else
		m_Player->SetVelocityX(0);
	

	//CAMERA
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


	//STATE CHANGE
	//if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
	//{
	//	StateManager::GetInstance()->m_GameStateStack.pop_back();
	//	StateManager::GetInstance()->AddState(StateManager::GetInstance()->GS_STATE_2);


	//	//ResetInstance();
	//}

	//Play sound+STATE CHANGE
	if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
	{
		static bool isSoundPlayed = false;
		if (isSoundPlayed == false) {

			SoundEngine::GetInstance()->Play(0, 0.5, 1.5, true);
			isSoundPlayed = true;
		}

	}

}

void SceneManager::AddObject(Object *object) {
	m_ObjectList.push_back(object);
}

void SceneManager::AddRoom(Room *room) {
	m_RoomList.push_back(room);
}

void SceneManager::AddEnemy(Enemy *enemy) {
	m_EnemyList.push_back(enemy);
}

bool SceneManager::CheckInRange(Vector2 roomID) {
	Vector2 currRoom = m_Player->m_RoomID;
	if (roomID.x < currRoom.x - 1 || roomID.x > currRoom.x + 1 ||
		roomID.y < currRoom.y - 1 || roomID.y > currRoom.y + 1)
		return false;
	else 
		return true;
}

void SceneManager::GetRenderOrder() {
	std::sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object *a, Object *b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) < (b->GetPosY() - b->m_fHeight));
	});
}