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
	m_Camera = new Camera(fPosX, fPosY, fLeft, fRight, fBottom, fTop, fNear, fFar, fMovingSpeed, fRotationSpeed);
	
	fclose(dataFile);

	MapGenerate(MAP_MAX_TUNNEL, TUNNEL_MAX_LENGTH);
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
			translation.SetTranslation(i * ROOM_WIDTH, j * ROOM_HEIGHT, -1.0f);
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

void SceneManager::CheckCollision()
{
	static bool isCollied = false;//test only
	
	bool testCheck=PhysicEngine::GetInstance()->CheckRectRectCollision(m_ObjectList[1], m_ObjectList[2]);
	
	
	if (isCollied==false&&testCheck == true) {
		printf("Collied!\n");
		isCollied = true;
	}
	else if (isCollied == true && testCheck == false) {
		printf("Not Collied!\n");
		isCollied = false;
	}
	
}

void SceneManager::Render() {
	//GetRenderOrder();
	for (auto& obj : m_RoomList) {
		obj->Render(this->m_Camera);
	}
	for (auto& obj : m_ObjectList) {
		obj->Render(this->m_Camera);
	}
	
}

void SceneManager::Update(float frameTime) {
	m_Camera->Update(frameTime);

	for (auto& object : m_ObjectList) {
		object->Update(frameTime);
	}

	Control(frameTime);
	
	//CheckCollision();
}

void SceneManager::Control(float frameTime)
{
	//testing

	//CHAR CONTROL
	float fSpeed = 5.0f;

	if (InputManager::GetInstance()->keyPressed & KEY_W)
	{
		m_ObjectList[1]->SetPosY(m_ObjectList[1]->GetPosY() + fSpeed*frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_A)
	{
		m_ObjectList[1]->SetPosX(m_ObjectList[1]->GetPosX() - fSpeed * frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_S)
	{
		m_ObjectList[1]->SetPosY(m_ObjectList[1]->GetPosY() - fSpeed * frameTime);
	}
	if (InputManager::GetInstance()->keyPressed & KEY_D)
	{
		m_ObjectList[1]->SetPosX(m_ObjectList[1]->GetPosX() + fSpeed * frameTime);
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
	delete m_Camera;

	delete s_Instance;
	s_Instance = NULL;
}