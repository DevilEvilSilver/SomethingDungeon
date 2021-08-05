#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "SceneManager.h"
#include "Object.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

#include "InputManager.h"
#include "StateManager.h"

#include "PhysicEngine.h"

template <class T>
T GetRoom(RoomType id, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (id == obj->m_RoomType)
			return obj;
	}
	return 0;
}

SceneManager * SceneManager::s_Instance = NULL;

SceneManager::SceneManager(void) {
	this->Init();
}

SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new SceneManager();
	return s_Instance;
}



void SceneManager::Init() {
	MapGenerate(MAP_MAX_TUNNEL, TUNNEL_MAX_LENGTH);
	Room *startRoom = GetRoom(START, m_RoomList);

	FILE* dataFile;
	dataFile = fopen(FILE_SM, "r");

	int iObjectCount;
	fscanf(dataFile, "#OBJECT_COUNT %d\n", &iObjectCount);

	while (iObjectCount--) {
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);

		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);

		Matrix translation;
		GLfloat x, y, z;
		fscanf(dataFile, "POSITION %f, %f, %f\n", &x, &y, &z);
		translation.SetTranslation(x, y, z);

		Object *object = new Object(strPrefab, translation);
		AddObject(object);
	}

	//Player
	fscanf(dataFile, "#PLAYER\n");
	unsigned int id;
	fscanf(dataFile, "ID %d\n", &id);
	char strPrefab[50];
	fscanf(dataFile, "PREFAB %s\n", &strPrefab);
	Matrix translation;
	GLfloat x, y, z;
	fscanf(dataFile, "POSITION %f, %f, %f\n", &x, &y, &z);
	translation.SetTranslation(x, y, z);
	m_Player = new Player(strPrefab, translation);
	m_Player->SetPosX(startRoom->GetPosX() + PLAYER_START_POSX);
	m_Player->SetPosY(startRoom->GetPosY() - startRoom->m_fHeight + PLAYER_START_POSY);

	//Camera
	fscanf(dataFile, "#CAMERA\n");
	float fPosX, fPosY;
	fscanf(dataFile, "POS %f, %f\n", &fPosX, &fPosY);
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
				Room *room = new Room(NORMAL_ROOM, translation, NORMAL);
				AddRoom(room);
			}
			else if (m_Map[i][j] == WALL) {
				Room *room = new Room(WALL_ROOM, translation, WALL);
				AddRoom(room);
			}
			else if (m_Map[i][j] == START) {
				Room *room = new Room(NORMAL_ROOM, translation, START);
				AddRoom(room);
			}
			else if (m_Map[i][j] == END) {
				Room *room = new Room(NORMAL_ROOM, translation, END);
				AddRoom(room);
			}
		}
	}
}

void SceneManager::Render() {
	//GetRenderOrder();
	for (auto& obj : m_RoomList) {
		obj->Render(this->m_Camera);
	}

	m_Player->Render(this->m_Camera);

	for (auto& object : m_EnemyList) {
		object->Render(this->m_Camera);
	}
}

void SceneManager::Update(float frameTime) {
	m_Camera->Update(frameTime);
	m_Player->Update(frameTime);

	for (auto& object : m_EnemyList) {
		object->Update(frameTime);
	}

	Control(frameTime);
}

void SceneManager::Control(float frameTime)
{
	//CHAR CONTROL
	float fSpeed = 15.0f;

	if (InputManager::GetInstance()->keyPressed & KEY_W)
	{
		m_Player->SetPosY(m_Player->GetPosY() + fSpeed*frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_A)
	{
		m_Player->SetPosX(m_Player->GetPosX() - fSpeed * frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_S)
	{
		m_Player->SetPosY(m_Player->GetPosY() - fSpeed * frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_D)
	{
		m_Player->SetPosX(m_Player->GetPosX() + fSpeed * frameTime);
	}
	
	//CAMERA
	if (InputManager::GetInstance()->keyPressed & KEY_UP)
	{
		m_Camera->MoveUp(frameTime);
		//m_ObjectList[0]->SetPosY(m_ObjectList[0]->GetPosY() + fSpeed * frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_LEFT)
	{
		m_Camera->MoveLeft(frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_DOWN)
	{
		m_Camera->MoveDown(frameTime);
		//m_ObjectList[0]->SetPosY(m_ObjectList[0]->GetPosY() - fSpeed * frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_RIGHT)
	{
		m_Camera->MoveRight(frameTime);
	}


	//STATE CHANGE
	if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
	{
		StateManager::GetInstance()->m_GameStateStack.pop_back();
		StateManager::GetInstance()->AddState(StateManager::GetInstance()->GS_STATE_2);


		//ResetInstance();
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

void SceneManager::GetRenderOrder() {
	std::sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object *a, Object *b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) < (b->GetPosY() - b->m_fHeight));
	});
}

void SceneManager::ResetInstance() {
	
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
	delete m_Camera;

	delete s_Instance;
	s_Instance = NULL;
}