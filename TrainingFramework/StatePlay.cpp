#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StatePlay.h"
#include "ResourceManager.h"
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
	for (auto& obj : objList) {
		if (id == obj->m_RoomType)
			return obj;
	}
	return 0;
}

template <class T>
T GetRoomByID(Vector2 roomID, std::vector<T> objList) {
	for (auto& obj : objList) {
		if (roomID.x == obj->m_RoomID.x && roomID.y == obj->m_RoomID.y)
			return obj;
	}
	return 0;
}

template <class T>
T GetResource(std::string id, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (!strcmp(id.c_str(), obj->m_strResourceID.c_str()))
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
	for (auto& object : m_DropList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_DropList.clear();

	for (auto& object : m_TrapList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_TrapList.clear();

	for (auto& object : m_DecorationList) {
		if (object != NULL) {
			delete object;
		}
		m_DecorationList.clear();
	}

	for (auto& object : m_EffectList) {
		if (object != NULL) {
			delete object;
		}
	}
	m_EffectList.clear();

	delete m_Player;
	delete m_Camera;

	//UI
	delete m_ButtonPause;
	delete m_PauseBox;
	delete m_ButtonResume;
	delete m_ButtonQuit;

	delete m_HpHolder;
	delete m_HpBar;
	delete m_HpText;
	delete m_MpHolder;
	delete m_MpBar;
	delete m_MpText;
	delete m_MeleeIcon;
	delete m_MeleeBar;
	delete m_RangeIcon;
	delete m_RangeBar;
	delete m_DashBar;
	delete m_DashIcon;
	delete m_GoldIcon;
	delete m_GoldText;
	delete m_MiniMap;
	delete m_GateInstruct;
	delete m_KeyIcon;
	delete m_KeyText;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
	if (m_DeathBanner != NULL)
		delete m_DeathBanner;
	}
void StatePlay::InitFloorID()
{
	FILE* recordFile;
	recordFile = fopen(FILE_RECORD, "r");
	char strFloor[50];
	fscanf(recordFile, "%s\n", &strFloor);
	unsigned int iTotalTime;
	fscanf(recordFile, "Time %d\n", &iTotalTime);
	m_TotalTime = (float)iTotalTime;
	fscanf(recordFile, "Kills %d\n", &m_TotalKill);
	fscanf(recordFile, "Golds %d\n", &m_TotalGold);
	fclose(recordFile);

	if (!strcmp(strFloor, FLOOR_1) || !strcmp(strFloor, RECORD_LOSE))
		m_floorID = FloorIdentify::FLOOR_1_ID;
	else if (!strcmp(strFloor, FLOOR_2))
		m_floorID = FloorIdentify::FLOOR_2_ID;
	else if (!strcmp(strFloor, FLOOR_3))
		m_floorID = FloorIdentify::FLOOR_3_ID;
	else if (!strcmp(strFloor, FLOOR_BOSS))
		m_floorID = FloorIdentify::FLOOR_BOSS_ID;
}

void StatePlay::Init() {
	InitFloorID();
	switch (m_floorID) {
	case FloorIdentify::FLOOR_1_ID:
		ResourceManager::GetInstance()->Init(FILE_R_PLAY_1);
		SoundEngine::GetInstance()->Init(FILE_SD_PLAY_1);
		break;
	case FloorIdentify::FLOOR_2_ID:
		ResourceManager::GetInstance()->Init(FILE_R_PLAY_2);
		SoundEngine::GetInstance()->Init(FILE_SD_PLAY_2);
		break;
	case FloorIdentify::FLOOR_3_ID:
		ResourceManager::GetInstance()->Init(FILE_R_PLAY_3);
		SoundEngine::GetInstance()->Init(FILE_SD_PLAY_3);
		break;
	case FloorIdentify::FLOOR_BOSS_ID:
	default:
		ResourceManager::GetInstance()->Init(FILE_R_PLAY_BOSS);
		SoundEngine::GetInstance()->Init(FILE_SD_PLAY_BOSS);
		break;
	}

	/*InitFloorID();
	switch (m_floorID)
	{
	case FloorIdentify::FLOOR_1_ID:
		break;
	case FloorIdentify::FLOOR_2_ID:
		break;
	case FloorIdentify::FLOOR_3_ID:
		break;
	case FloorIdentify::FLOOR_BOSS_ID:
		break;
	}*/
	if (m_floorID != FloorIdentify::FLOOR_BOSS_ID)
		MapGenerate(MAP_MAX_TUNNEL, TUNNEL_MAX_LENGTH);
	else
		MapBossGenerate();
	Room* startRoom = GetRoomByType(START, m_RoomList);

	FILE* dataFile;
	dataFile = fopen(FILE_S_PLAY, "r");

	//Player
	fscanf(dataFile, "#PLAYER\n");
	char strPrefab[50];
	fscanf(dataFile, "PREFAB %s\n", &strPrefab);
	Matrix translation;
	translation.SetTranslation(startRoom->GetPosX() + ROOM_WIDTH / 2.0f, startRoom->GetPosY() - ROOM_HEIGHT / 2, 0.0f);
	m_Player = new Player(strPrefab, startRoom->m_RoomID, translation);
	translation.SetTranslation(m_Player->GetPosX() + 1, m_Player->GetPosY() + 1, 0);

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

	//HP Holder
	{
		fscanf(dataFile, "#HP_HOLDER\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_HpHolder = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//HP Bar
	{
		fscanf(dataFile, "#HP_BAR\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_HpBar = new Bar(strPrefab, Vector2(0.0f, 0.0f), translation, m_Player->m_maxHP, m_Player->m_currHP);
	}

	//MP Holder
	{
		fscanf(dataFile, "#MP_HOLDER\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_MpHolder = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//MP Bar
	{
		fscanf(dataFile, "#MP_BAR\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_MpBar = new Bar(strPrefab, Vector2(0.0f, 0.0f), translation, m_Player->m_maxMP, m_Player->m_currMP);
	}

	//Melee Icon
	{
		fscanf(dataFile, "#MELEE_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		if (!strcmp(m_Player->GetCloseSkill().c_str(), SKILL_FIRE1))
			m_MeleeIcon = new Widget(ICON_FLAME_SWORD, Vector2(0.0f, 0.0f), translation);
		else if (!strcmp(m_Player->GetCloseSkill().c_str(), SKILL_FIRE2))
			m_MeleeIcon = new Widget(ICON_PYRO_WAVE, Vector2(0.0f, 0.0f), translation);
		else 
			m_MeleeIcon = new Widget(ICON_SOLAR_DESCEND, Vector2(0.0f, 0.0f), translation);
	}

	//Melee Bar
	{
		fscanf(dataFile, "#MELEE_BAR\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_MeleeBar = new Bar(strPrefab, Vector2(0.0f, 0.0f), translation, m_Player->GetCloseSkillMaxCD(), m_Player->GetCloseSkillCurrCD(), false);
	}

	//Range Icon
	{
		fscanf(dataFile, "#RANGE_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		if (!strcmp(m_Player->GetRangeSkill().c_str(), SKILL_FREEZE1))
			m_RangeIcon = new Widget(ICON_ICE_ARROW, Vector2(0.0f, 0.0f), translation);
		else if (!strcmp(m_Player->GetRangeSkill().c_str(), SKILL_FREEZE2))
			m_RangeIcon = new Widget(ICON_GLACIAL_BLAST, Vector2(0.0f, 0.0f), translation);
		else
			m_RangeIcon = new Widget(ICON_ABSOLUTE_ZERO, Vector2(0.0f, 0.0f), translation);
	}

	//Range Bar
	{
		fscanf(dataFile, "#RANGE_BAR\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_RangeBar = new Bar(strPrefab, Vector2(0.0f, 0.0f), translation, m_Player->GetRangeSkillMaxCD(), m_Player->GetRangeSkillCurrCD(), false);
	}
	//DASH ICON
	{
		fscanf(dataFile, "#DASH_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_DashIcon = new Widget(ICON_DASH, Vector2(0.0f, 0.0f), translation);
	}

	//DASH BAR
	{
		fscanf(dataFile, "#DASH_BAR\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_DashBar = new Bar(strPrefab, Vector2(0.0f, 0.0f), translation, m_Player->GetDashSkillMaxCD(), m_Player->GetDashSkillCurrCD(), false);
	}
	//Gold Icon
	{
		fscanf(dataFile, "#GOLD_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_GoldIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Key Icon
	{
		fscanf(dataFile, "#KEY_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_KeyIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Pause Box
	{
		fscanf(dataFile, "#PAUSE_BOX\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_PauseBox = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Button Pause
	{
		fscanf(dataFile, "#BUTTON_PAUSE\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonPause = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Button Resume
	{
		fscanf(dataFile, "#BUTTON_RESUME\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonResume = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Button Quit
	{
		fscanf(dataFile, "#BUTTON_QUIT\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonQuit = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}
	//MiniMap
	{
		fscanf(dataFile, "#MINIMAP\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);

		m_MiniMap = new MiniMap(translation, (RoomType*)m_Map, m_Camera, m_Player);
	}

	//Gate Instruct
	{
		fscanf(dataFile, "#GATE_INSTRUCT\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_GateInstruct = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	fclose(dataFile);

	//INIT LOGIC
	m_isWinSFX = false;
	m_isGateInstruct = false;
	m_isNextState = false;
	m_isDead = false;
	m_isQuit = false;
	m_isStartUp = false;
	m_fNextStateFrame = 1.0f;
	m_StartUpGold = std::stoi(m_Player->GetGold());
	m_DeathBanner = NULL;
	m_TransitionScreen = NULL;

	//INIT TEXT
	m_HpText = new Text(m_Player->GetHP(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 330.0f, 654.0f, 1.0f);
	m_MpText = new Text(m_Player->GetMP(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 330.0f, 699.0f, 1.0f);
	m_GoldText = new Text(m_Player->GetGold(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 1025.0f, 700.0f, 1.0f, TEXT_ALIGN::RIGHT);
	m_KeyText = new Text(m_Player->GetKey(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 1025.0f, 655.0f, 1.0f, TEXT_ALIGN::RIGHT);
}

void StatePlay::MapGenerate(unsigned int maxTunnel, unsigned int maxLength) {
	std::fill_n(*m_Map, sizeof(m_Map) / sizeof(**m_Map), WALL);
	srand(time(NULL));
	unsigned int currPosX = rand() % (MAP_WIDTH - 2) + 1;
	unsigned int currPosY = rand() % (MAP_HEIGHT - 2) + 1;
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
				(currPosX == (MAP_WIDTH - 2)) && (directions[randDirection].x == 1) ||
				(currPosY == 1) && (directions[randDirection].y == -1) ||
				(currPosY == (MAP_HEIGHT - 2)) && (directions[randDirection].y == 1)) {
				break;
			}
			else {
				if (m_Map[currPosX][currPosY] != START &&
					m_Map[currPosX][currPosY] != KEY_ROOM)
					m_Map[currPosX][currPosY] = NORMAL;
				currPosX += directions[randDirection].x;
				currPosY += directions[randDirection].y;
				lastDirection = randDirection;
			}
		}

		switch (maxTunnel) {
		case 20:
		case 40:
		case 60:
			m_Map[currPosX][currPosY] = KEY_ROOM;
			break;
		}
	}


	m_Map[currPosX][currPosY] = END;

	for (unsigned int i = 0; i < MAP_WIDTH; i++) {
		for (unsigned int j = 0; j < MAP_HEIGHT; j++) {
			Matrix translation;
			translation.SetTranslation(i * ROOM_WIDTH, (j + 1) * ROOM_HEIGHT, -1.0f);
			if (m_Map[i][j] == NORMAL) {
				Room* room;
				switch (rand() % 5 + 1)
				{
				case 1:
					room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, NORMAL);

					break;
				case 2:
					room = new Room(NORMAL_ROOM_2, Vector2(i, j), translation, NORMAL);
					break;
				case 3:
					room = new Room(NORMAL_ROOM_3, Vector2(i, j), translation, NORMAL);
					break;
				case 4:
					room = new Room(NORMAL_ROOM_4, Vector2(i, j), translation, NORMAL);
					break;
				case 5:
					room = new Room(NORMAL_ROOM_5, Vector2(i, j), translation, NORMAL);
					break;
				}
				if (rand() % 2 == 0) room->m_isFacingLeft = false;
				AddRoom(room);
			}
			else if (m_Map[i][j] == WALL) {
				
				if (m_Map[i][j - 1] == WALL) {
					
					Room* room = new Room(WALL_ROOM, Vector2(i, j), translation, WALL);
					/*if (m_Map[i][j + 1] != WALL)
					{
						room->SetPosY2(room->GetPosY() - 0.2f);
						room->m_fHeight - 0.2f;
						room->m_isRenderLast = true;
					}*/
					AddRoom(room);
				}
				else {
					Room* room;
					switch (rand() % 4 + 1)
					{
					case 1:
						room = new Room(BORDER_ROOM_1_1, Vector2(i, j), translation, WALL);
						break;
					case 2:
						room = new Room(BORDER_ROOM_1_2, Vector2(i, j), translation, WALL);
						break;
					case 3:
						room = new Room(BORDER_ROOM_1_3, Vector2(i, j), translation, WALL);
						break;
					case 4:
						room = new Room(BORDER_ROOM_1_4, Vector2(i, j), translation, WALL);
						break;
					}
					if (rand() % 2 == 0) room->m_isFacingLeft = false;
					/*if (m_Map[i][j + 1] != WALL)
					{
						room->SetPosY2(room->GetPosY() - 0.4f);
						room->m_isRenderLast = true;
					}*/
					AddRoom(room);
				}
			}
			else if (m_Map[i][j] == START) {
				Room* room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, START);
				AddRoom(room);
			}
			else if (m_Map[i][j] == END) {
				Room* room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, END);
				AddRoom(room);
			}
			else if (m_Map[i][j] == KEY_ROOM) {
				Room* room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, KEY_ROOM);
				AddRoom(room);
			}
		}
	}
}

void StatePlay::MapBossGenerate() {
	m_Map[0][0] = WALL; m_Map[0][1] = WALL; m_Map[0][2] = WALL; m_Map[0][3] = WALL; m_Map[0][4] = WALL; m_Map[0][5] = WALL;
	m_Map[1][0] = WALL; m_Map[1][1] = WALL; m_Map[1][2] = NORMAL; m_Map[1][3] = NORMAL; m_Map[1][4] = NORMAL; m_Map[1][5] = WALL;
	m_Map[2][0] = WALL; m_Map[2][1] = WALL; m_Map[2][2] = START; m_Map[2][3] = NORMAL; m_Map[2][4] = END; m_Map[2][5] = WALL;
	m_Map[3][0] = WALL; m_Map[3][1] = WALL; m_Map[3][2] = NORMAL; m_Map[3][3] = NORMAL; m_Map[3][4] = NORMAL; m_Map[3][5] = WALL;
	m_Map[4][0] = WALL; m_Map[4][1] = WALL; m_Map[4][2] = WALL; m_Map[4][3] = WALL; m_Map[4][4] = WALL; m_Map[4][5] = WALL;

	for (unsigned int i = 0; i < 5; i++) {
		for (unsigned int j = 0; j < 6; j++) {
			Matrix translation;
			translation.SetTranslation(i * ROOM_WIDTH, (j + 1) * ROOM_HEIGHT, -1.0f);
			if (m_Map[i][j] == NORMAL) {
				Room* room;
				switch (rand() % 5 + 1)
				{
				case 1:
					room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, NORMAL);

					break;
				case 2:
					room = new Room(NORMAL_ROOM_2, Vector2(i, j), translation, NORMAL);
					break;
				case 3:
					room = new Room(NORMAL_ROOM_3, Vector2(i, j), translation, NORMAL);
					break;
				case 4:
					room = new Room(NORMAL_ROOM_4, Vector2(i, j), translation, NORMAL);
					break;
				case 5:
					room = new Room(NORMAL_ROOM_5, Vector2(i, j), translation, NORMAL);
					break;
				}
				if (rand() % 2 == 0) room->m_isFacingLeft = false;
				AddRoom(room);
			}
			else if (m_Map[i][j] == WALL) {

				if (m_Map[i][j - 1] == WALL) {

					Room* room = new Room(WALL_ROOM, Vector2(i, j), translation, WALL);
					/*if (m_Map[i][j + 1] != WALL)
					{
						room->SetPosY2(room->GetPosY() - 0.2f);
						room->m_fHeight - 0.2f;
						room->m_isRenderLast = true;
					}*/
					AddRoom(room);
				}
				else {
					Room* room;
					switch (rand() % 4 + 1)
					{
					case 1:
						room = new Room(BORDER_ROOM_1_1, Vector2(i, j), translation, WALL);
						break;
					case 2:
						room = new Room(BORDER_ROOM_1_2, Vector2(i, j), translation, WALL);
						break;
					case 3:
						room = new Room(BORDER_ROOM_1_3, Vector2(i, j), translation, WALL);
						break;
					case 4:
						room = new Room(BORDER_ROOM_1_4, Vector2(i, j), translation, WALL);
						break;
					}
					if (rand() % 2 == 0) room->m_isFacingLeft = false;
					/*if (m_Map[i][j + 1] != WALL)
					{
						room->SetPosY2(room->GetPosY() - 0.4f);
						room->m_isRenderLast = true;
					}*/
					AddRoom(room);
				}
			}
			else if (m_Map[i][j] == START) {
				Room* room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, START);
				AddRoom(room);
			}
			else if (m_Map[i][j] == END) {
				Room* room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, END);
				AddRoom(room);
			}
			else if (m_Map[i][j] == KEY_ROOM) {
				Room* room = new Room(NORMAL_ROOM_1, Vector2(i, j), translation, KEY_ROOM);
				AddRoom(room);
			}
		}
	}
}

void StatePlay::RoomsGenerate() {
	//static bool once = false; if (once == false) once = true;  else		//when load directly stateplay
		for (auto& obj : m_RoomList) {

			obj->RoomGenerate();
		}
}

void StatePlay::Render() {
	GetRenderOrder();

	//RENDER ROOM
	{
		for (auto& obj : m_InRangeRoom) {
			if (obj->m_isRenderLast==false)
			obj->Render(this->m_Camera);
		}
	}

	//RENDER TRAP
	for (auto& obj : m_InRangeTrap) {
		if (strcmp(typeid(*obj).name(), "class ArrowTower") != 0 || strcmp(typeid(*obj).name(), "class Chest") != 0)
		obj->Render(this->m_Camera);
	}

	//RENDER DROP
	for (auto& obj : m_InRangeDrop) {
		obj->Render(this->m_Camera);
	}


	//RENDER OBJECT
	{
		for (auto& obj : m_ObjectList) {
			obj->Render(this->m_Camera);
		}
	}
	m_ObjectList.clear();

	//RENDER SKILL
	for (auto& obj : m_InRangeSkill)
	{
		obj->Render(this->m_Camera);
	}

	for (auto& obj : m_InRangeEffect)
	{
		obj->Render(this->m_Camera);
	}
	

	//RENDER EFFECT
	
	//RENDER UI
	{
		m_HpHolder->Render(m_Camera);
		m_HpBar->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_HpText);

		m_MpHolder->Render(m_Camera);
		m_MpBar->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_MpText);

		m_MeleeIcon->Render(m_Camera);
		m_MeleeBar->Render(m_Camera);

		m_RangeIcon->Render(m_Camera);
		m_RangeBar->Render(m_Camera);

		m_DashIcon->Render(m_Camera);
		m_DashBar->Render(m_Camera);

		m_GoldIcon->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_GoldText);

		m_KeyIcon->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_KeyText);

		m_ButtonPause->Render(m_Camera);
		if (m_isPause) {
			m_PauseBox->Render(m_Camera);
			m_ButtonResume->Render(m_Camera);
			m_ButtonQuit->Render(m_Camera);
		}
		
		//MiniMap
		if (m_floorID != FloorIdentify::FLOOR_BOSS_ID)
			m_MiniMap->Render(m_Camera);

		//Gate instruct
		if (m_isGateInstruct) {
			m_GateInstruct->Render(m_Camera);
		}

		if (m_DeathBanner != NULL)
			m_DeathBanner->Render(this->m_Camera);
		if (m_TransitionScreen != NULL)
			m_TransitionScreen->Render(this->m_Camera);
	}
}
void StatePlay::AddDrop(Drop* drop)
{
	m_DropList.push_back(drop);
}
void StatePlay::AddTrap(Trap* trap)
{
	m_TrapList.push_back(trap);
}
void StatePlay::AddEffect(Effect* effect)
{
	m_EffectList.push_back(effect);
}
void StatePlay::Remove()
{
	//Kill enemy
	for (auto& obj : m_EnemyList) {
		if (obj->isDead == true)
		{
			RemoveEnemy(obj);
		}
	}

	//Delete drop
	for (auto& obj : m_DropList)
	{
		if (obj->isPicked == true)
		{
			RemoveDrop(obj);
		}
	}

	//Delete trap
	for (auto& obj : m_TrapList)
	{
		if (obj->isExploded == true)
		{
			RemoveTrap(obj);
		}
	}

	//delete skill
	for (auto& obj : m_SkillList)
	{
		if (obj->isFinished == true)
		{
			RemoveSkill(obj);
		}
	}
	//delete effect
	for (auto& obj : m_EffectList)
	{
		if (obj->mp_isFisnished == true)
		{
			RemoveEffect(obj);
		}
	}

	for (auto& obj : m_DecorationList)
	{
		if (obj->hp <= 0)
		{

			SoundEngine::GetInstance()->Play(BOMB, 1.0f, 1.5f, false);
			RemoveDecoration(obj);

		}
	}


}
void StatePlay::RemoveDrop(Drop* drop)
{
	int id;
	for (int i = 0; i < m_DropList.size(); i++) {
		if (m_DropList[i] == drop)  id = i;
	}

	delete m_DropList[id];
	m_DropList[id] = m_DropList[m_DropList.size() - 1];

	m_DropList.resize(m_DropList.size() - 1);
}
void StatePlay::RemoveTrap(Trap* trap)
{
	int id;
	for (int i = 0; i < m_TrapList.size(); i++) {
		if (m_TrapList[i] == trap)  id = i;
	}

	delete m_TrapList[id];
	m_TrapList[id] = m_TrapList[m_TrapList.size() - 1];

	m_TrapList.resize(m_TrapList.size() - 1);
}

void StatePlay::Update(float frameTime) {
	m_TotalTime += frameTime;

	if (!m_isDead && !m_isNextState) {
		if (!m_isStartUp) {
			RoomsGenerate();
			m_iHandleBGM = SoundEngine::GetInstance()->Play(PLAY_BGM, 0.5f, 1.0f, true);
			m_isStartUp = true;
		}
		else {
			if (m_isPause) {
				m_PauseBox->Update(frameTime);
				m_ButtonResume->Update(frameTime);
				m_ButtonQuit->Update(frameTime);

				UpdatePause(frameTime);
			}
			else {
				//CHECK IF PLAYER DEAD 
				if (m_Player->m_currHP <= 0) {
					m_isDead = true;
				}
		
				Remove();
				UpdateInRange();
				UpdateRoomID();

				for (auto& obj : m_InRangeRoom) {
					obj->Update(frameTime);
				}
				m_Player->Update(frameTime);
				for (auto& obj : m_InRangeEnemy) {
						obj->Update(frameTime);
				}
				for (auto& obj : m_InRangeSkill) {
						obj->Update(frameTime);
				}
				for (auto& obj : m_InRangeTrap) {
						obj->Update(frameTime);
				}
				for (auto& obj : m_InRangeDrop) {
						obj->Update(frameTime);
				}
				for (auto& obj : m_InRangeEffect) 
				{
					obj->Update(frameTime);
				}

				UpdateControl(frameTime);

				//follow camera
				m_Camera->SetPosition(Vector3(m_Player->GetPosX(), m_Player->GetPosY(), m_Camera->GetPosition().z));
				m_Camera->Update(frameTime);

				//Update UI
				m_ButtonPause->Update(frameTime);

				m_HpHolder->Update(frameTime);
				m_HpBar->Update(frameTime);
				m_HpBar->Resize(m_Player->m_currHP);
				m_HpText->setText(m_Player->GetHP());

				m_MpHolder->Update(frameTime);
				m_MpBar->Update(frameTime);
				m_MpBar->Resize(m_Player->m_currMP);
				m_MpText->setText(m_Player->GetMP());

				m_MeleeIcon->Update(frameTime);
				m_MeleeBar->Update(frameTime);
				m_MeleeBar->Resize(m_Player->GetCloseSkillCurrCD());

				m_DashIcon->Update(frameTime);
				m_DashBar->Update(frameTime);
				m_DashBar->Resize(m_Player->GetDashSkillCurrCD());

				m_RangeIcon->Update(frameTime);
				m_RangeBar->Update(frameTime);
				m_RangeBar->Resize(m_Player->GetRangeSkillCurrCD());

				m_GoldIcon->Update(frameTime);
				m_GoldText->setText(m_Player->GetGold());

				m_KeyIcon->Update(frameTime);
				m_KeyText->setText(m_Player->GetKey());
				
				if (m_floorID == FloorIdentify::FLOOR_BOSS_ID) {
					if (m_EnemyList.size() < 1 && !m_isWinSFX) {
						SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, 0.5f);
						m_iHandleBGM = SoundEngine::GetInstance()->Play(WIN_SFX, 0.5f, 1.0f, false);
						m_isWinSFX = true;
					}
				}
				else
					m_MiniMap->Update(frameTime);

				if (m_isGateInstruct) {
					m_GateInstruct->Update(frameTime);
				}
			}
		}
	}
	else {
		UpdateResult(frameTime);
	}

	if (m_DeathBanner != NULL)
		m_DeathBanner->Update(frameTime);
	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);
}

void StatePlay::UpdateInRange()
{
	ClearInRange();

	for (auto& obj : m_RoomList) if (CheckInRange(obj->m_RoomID,2) == true) m_InRangeRoom.push_back(obj);
	for (auto& obj : m_EnemyList) if (CheckInRange(obj->m_RoomID,2) == true) m_InRangeEnemy.push_back(obj);
	for (auto& obj : m_DropList) if (CheckInRange(obj->m_RoomID) == true) m_InRangeDrop.push_back(obj);

	for (auto& obj : m_TrapList)
		if (CheckInRange(obj->m_RoomID) == true/*|| strcmp(typeid(obj).name(), "Arrow")==0*/)
			m_InRangeTrap.push_back(obj);
		else if (strcmp(typeid(*obj).name(), "class Arrow") == 0)
			obj->isExploded = true;
	
	for (auto& obj : m_SkillList)
		if (CheckInRange(obj->m_RoomID) == true)
			m_InRangeSkill.push_back(obj);
		else obj->isFinished = true;
				
	for (auto& obj : m_DecorationList) if (CheckInRange(obj->m_RoomID,2) == true) m_InRangeDecoration.push_back(obj);
	for (auto& obj : m_EffectList) 
		if (CheckInRange(obj->m_RoomID) == true) 
			m_InRangeEffect.push_back(obj);
		else obj->mp_isFisnished = true;
	/*printf("Room Count:\t%d\n",m_InRangeRoom.size());
	printf("Enemy Count:\t%d\n", m_InRangeEnemy.size());
	printf("Drop Count:\t%d\n", m_InRangeDrop.size());
	printf("Trap Count:\t%d\n", m_InRangeTrap.size());
	printf("Skill Count:\t%d\n", m_InRangeSkill.size());
	printf("DecorationCount:\t%d\n", m_InRangeDecoration.size());
	printf("Effect Count:\t%d\n", m_InRangeEffect.size());
	printf("\n\n\n");*/
}

void StatePlay::ClearInRange()
{
	m_InRangeRoom.clear();
	m_InRangeDrop.clear();
	m_InRangeEnemy.clear();
	m_InRangeSkill.clear();
	m_InRangeTrap.clear();
	m_InRangeDecoration.clear();
	m_InRangeEffect.clear();
}

void StatePlay::UpdateRoomID() {
	if (!CollisionManager::CheckCollision(m_Player, GetRoomByID(m_Player->m_RoomID, m_RoomList))) {
		for (unsigned int i = m_Player->m_RoomID.x - 1; i <= m_Player->m_RoomID.x + 1; i++) {
			if (i > MAP_WIDTH - 1)
				continue;

			for (unsigned int j = m_Player->m_RoomID.y - 1; j <= m_Player->m_RoomID.y + 1; j++) {
				if (j > MAP_HEIGHT - 1)
					continue;
				if (CollisionManager::CheckCollision(m_Player, GetRoomByID(Vector2(i, j), m_RoomList))) {
					m_Player->m_RoomID = Vector2(i, j);
					break;
				}

			}
		}
	}

	for (auto& obj : m_InRangeEnemy) {

		{
			if (!CollisionManager::CheckCollision(obj, GetRoomByID(obj->m_RoomID, m_RoomList))) 
			for (unsigned int i = obj->m_RoomID.x - 1; i <= obj->m_RoomID.x + 1; i++) {
				if (i > MAP_WIDTH - 1)
					continue;

				for (unsigned int j = obj->m_RoomID.y - 1; j <= obj->m_RoomID.y + 1; j++) {
					if (j > MAP_HEIGHT - 1)
						continue;
						if (CollisionManager::CheckCollision(obj, GetRoomByID(Vector2(i, j), m_RoomList))) {
							obj->m_RoomID = Vector2(i, j);
							break;
						}
					}
				}
		}
	}

	for (auto& obj : m_InRangeSkill) {
		{
			if (!CollisionManager::CheckCollision(obj, GetRoomByID(obj->m_RoomID, m_RoomList)))
				for (unsigned int i = obj->m_RoomID.x - 1; i <= obj->m_RoomID.x + 1; i++) {
					if (i > MAP_WIDTH - 1)
						continue;

					for (unsigned int j = obj->m_RoomID.y - 1; j <= obj->m_RoomID.y + 1; j++) {
						if (j > MAP_HEIGHT - 1)
							continue;
						if (CollisionManager::CheckCollision(obj, GetRoomByID(Vector2(i, j), m_RoomList))) {
							obj->m_RoomID = Vector2(i, j);
							break;
						}
					}
				}
		}
	}

	for (auto& obj : m_InRangeTrap) {
		{
			if (strcmp(typeid(*obj).name(), "class Arrow") == 0)
			if (!CollisionManager::CheckCollision(obj, GetRoomByID(obj->m_RoomID, m_RoomList)))
				for (unsigned int i = obj->m_RoomID.x - 1; i <= obj->m_RoomID.x + 1; i++) {
					if (i > MAP_WIDTH - 1)
						continue;

					for (unsigned int j = obj->m_RoomID.y - 1; j <= obj->m_RoomID.y + 1; j++) {
						if (j > MAP_HEIGHT - 1)
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

	//BUTTON PAUSE
	if (m_ButtonPause->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->SetPauseAll(true);
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isPause = true;
		return;
	}
	if (m_ButtonPause->isPressed(this->m_Camera)) {
		return;
	}
	m_ButtonPause->isHover(this->m_Camera);

	//PLAYER
	if (m_Player->m_pState==m_Player->P_CS)
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
		m_Player->UseSkill(frameTime);
	}

	

	//CAMERA
	/*{
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
	}*/

	//USING SPACE	~	TEST
	//m_Player->UseAttack();

	// if (newKeyPressed & KEY_SPACE)
	// {
	// 	m_Player->Dash(frameTime);
	// }
}

void StatePlay::UpdatePause(float frameTime) {
	//Button Resume
	if (m_ButtonResume->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->SetPauseAll(false);
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isPause = false;
		return;
	}
	m_ButtonResume->isPressed(this->m_Camera);
	m_ButtonResume->isHover(this->m_Camera);

	//Button Quit
	if (m_ButtonQuit->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isQuit = true;
		m_ButtonResume->m_isAvailble = false;
		m_ButtonQuit->m_isAvailble = false;
	}
	m_ButtonQuit->isPressed(this->m_Camera);
	m_ButtonQuit->isHover(this->m_Camera);

	//Play State
	if (m_isQuit) {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);

			SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 0) {
			//DONT SAVE RECORD HERE

			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();
			InputManager::GetInstance()->ResetInput();

			StateManager::GetInstance()->CloseState();
			return;
		}
	}
}

void StatePlay::UpdateResult(float frameTime) {
	//Death
	if (m_isDead) {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 6.0f && m_DeathBanner == NULL) {
			Matrix translation;
			float fTransY = GetResource(DEATH_BANNER, ResourceManager::GetInstance()->m_PrefabList)->m_fHeight / 2;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, fTransY, 2.0f);
			m_DeathBanner = new Fader(DEATH_BANNER, Vector2(0.0f, 0.0f), translation, 3.0f, 1.5f);

			m_fNextStateFrame += 5.0f;
			SoundEngine::GetInstance()->Play(DEATH_SFX, 3.0f, 1.0f, true);
			SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 2.0f);

			SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 0) {
			SetRecord(false);

			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();
			InputManager::GetInstance()->ResetInput();
			
			StateManager::GetInstance()->ClosenLoadState(GS_STATE_RESULT);
			return;
		}
	}
	else {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 2.0f);

			//TELEPORT ANIMATION !!!!!
			SoundEngine::GetInstance()->Play(TELEPORT_SFX, 3.0f, 1.0f, true);
			SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 0) {
			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();
			InputManager::GetInstance()->ResetInput();

			if (!SetRecord(true))
				StateManager::GetInstance()->ClosenLoadState(GS_STATE_SHOP);
			else
				StateManager::GetInstance()->ClosenLoadState(GS_STATE_RESULT);
			return;
		}
	}
}

bool StatePlay::SetRecord(bool isWin) {
	m_TotalGold += std::stoi(m_Player->GetGold()) - m_StartUpGold;

	bool isEndGame = false;
	FILE* recordFile;

	//read
	recordFile = fopen(FILE_RECORD, "r");
	char strFloor[50];
	fscanf(recordFile, "%s\n", &strFloor);
	fclose(recordFile);

	//write
	recordFile = fopen(FILE_RECORD, "w");

	if (isWin) {
		if (!strcmp(strFloor, FLOOR_1))
			fprintf(recordFile, "%s\n", FLOOR_2);
		else if (!strcmp(strFloor, FLOOR_2))
			fprintf(recordFile, "%s\n", FLOOR_3);
		else if (!strcmp(strFloor, FLOOR_3))
			fprintf(recordFile, "%s\n", FLOOR_BOSS);
		else {
			fprintf(recordFile, "%s\n", RECORD_WIN);
			isEndGame = true;
		}
	}
	else {
		fprintf(recordFile, "%s\n", RECORD_LOSE);
		isEndGame = true;
	}
	fprintf(recordFile, "Time %d\n", (int)m_TotalTime);
	fprintf(recordFile, "Kills %d\n", m_TotalKill);
	fprintf(recordFile, "Golds %d\n", m_TotalGold);
	fprintf(recordFile, "CurrHP %d\n", m_Player->m_currHP);
	fprintf(recordFile, "MaxHP %d\n", m_Player->m_maxHP);
	fprintf(recordFile, "CurrMP %d\n", m_Player->m_currMP);
	fprintf(recordFile, "MaxMP %d\n", m_Player->m_maxMP);
	fprintf(recordFile, "ATK %d\n", m_Player->m_ATK);
	fprintf(recordFile, "DEF %d\n", m_Player->m_DEF);
	fprintf(recordFile, "Gold %d\n", m_Player->m_GOLD);
	fprintf(recordFile, "Key %d\n", m_Player->m_KEY);
	fprintf(recordFile, "Speed %f\n", m_Player->m_MOVESPEED);
	fprintf(recordFile, "Melee %s\n", m_Player->GetCloseSkill().c_str());
	fprintf(recordFile, "Range %s\n", m_Player->GetRangeSkill().c_str());

	fclose(recordFile);

	return isEndGame;
}

void StatePlay::AddObject(Object *object) {
	m_ObjectList.push_back(object);
}
void StatePlay::AddRoom(Room* room) {
	m_RoomList.push_back(room);
}
void StatePlay::AddEnemy(Enemy* enemy) {
	m_EnemyList.push_back(enemy);
}
void StatePlay::AddDecoration(Decorations* decoration)
{
	m_DecorationList.push_back(decoration);
}
void StatePlay::AddSkill(Skill* skill)
{
	m_SkillList.push_back(skill);
}

bool StatePlay::CheckInRange(Vector2 roomID,int delta) {

	
	Vector2 currRoom = m_Player->m_RoomID;
	if (roomID.x < currRoom.x - delta || roomID.x > currRoom.x + delta ||
		roomID.y < currRoom.y - delta || roomID.y > currRoom.y + delta)
		return false;
	else
		return true;
}
void StatePlay::GetRenderOrder() {
	for (auto a : m_InRangeEnemy) {
		m_ObjectList.push_back(a);
	}
	m_ObjectList.push_back(m_Player);

	for (auto a : m_InRangeDecoration) {
		m_ObjectList.push_back(a);
	}

	for (auto& obj : StatePlay::GetInstance()->m_InRangeTrap) {
		if (strcmp(typeid(*obj).name(), "class ArrowTower") == 0 || strcmp(typeid(*obj).name(), "class Chest") == 0)
		{
			m_ObjectList.push_back(obj);
		}
	}

	std::stable_sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object* a, Object* b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) > (b->GetPosY() - b->m_fHeight));
		});
}

void StatePlay::RemoveEnemy(Enemy* enemy) {

	m_TotalKill++;

	//enemy->getGold()->m_isDisplay = true;
	int id;
	for (int i = 0; i < m_EnemyList.size(); i++) {
		if (m_EnemyList[i] == enemy)  id = i;
	}

	delete m_EnemyList[id];
	m_EnemyList[id] = NULL;
	m_EnemyList[id] = m_EnemyList[m_EnemyList.size() - 1];
	m_EnemyList.resize(m_EnemyList.size() - 1);
}

void StatePlay::RemoveSkill(Skill* skill)
{
	int id;
	for (int i = 0; i < m_SkillList.size(); i++) {
		if (m_SkillList[i] == skill)  id = i;
	}

	delete m_SkillList[id];
	m_SkillList[id] = m_SkillList[m_SkillList.size() - 1];
	m_SkillList.resize(m_SkillList.size() - 1);
}

void StatePlay::RemoveDecoration(Decorations* deco)
{
	int id;
	for (int i = 0; i < m_DecorationList.size(); i++) {
		if (m_DecorationList[i] == deco)  id = i;
	}

	delete m_DecorationList[id];
	m_DecorationList[id] = m_DecorationList[m_DecorationList.size() - 1];
	m_DecorationList.resize(m_DecorationList.size() - 1);
}
void StatePlay::RemoveEffect(Effect* effect)
{
	int id;
	for (int i = 0; i < m_EffectList.size(); i++) {
		if (m_EffectList[i] == effect)  id = i;
	}

	delete m_EffectList[id];
	m_EffectList[id] = m_EffectList[m_EffectList.size() - 1];
	m_EffectList.resize(m_EffectList.size() - 1);
}
