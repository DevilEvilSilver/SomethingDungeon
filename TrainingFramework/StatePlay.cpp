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
	delete m_GoldIcon;
	delete m_GoldText;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
}

void StatePlay::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_PLAY);

	MapGenerate(MAP_MAX_TUNNEL, TUNNEL_MAX_LENGTH);
	Room *startRoom = GetRoomByType(START, m_RoomList);

	FILE* dataFile;
	dataFile = fopen(FILE_S_PLAY, "r");

	//Player
	fscanf(dataFile, "#PLAYER\n");
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

	//HP Holder
	{
		fscanf(dataFile, "#HP_HOLDER\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
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
		translation.SetTranslation(x, y, 0.0f);
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
		translation.SetTranslation(x, y, 0.0f);
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
		translation.SetTranslation(x, y, 0.0f);
		m_MpBar = new Bar(strPrefab, Vector2(0.0f, 0.0f), translation, m_Player->m_maxMP, m_Player->m_currMP);
	}

	//Gold Icon
	{
		fscanf(dataFile, "#GOLD_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
		m_GoldIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Pause Box
	{
		fscanf(dataFile, "#PAUSE_BOX\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
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
		translation.SetTranslation(x, y, 0.0f);
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
		translation.SetTranslation(x, y, 0.0f);
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
		translation.SetTranslation(x, y, 0.0f);
		m_ButtonQuit = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	fclose(dataFile);

	m_isQuit = false;
	m_isStartUp = false;
	m_fNextStateFrame = 1.0f;
	m_TransitionScreen = NULL;

	m_HpText = new Text(m_Player->GetHP(), 1, 1, TEXT_COLOR::WHILE, 367.5f, 640.5f, 1.0f);
	m_MpText = new Text(m_Player->GetMP(), 1, 1, TEXT_COLOR::WHILE, 367.5f, 700.5f, 1.0f);
	m_GoldText = new Text(m_Player->GetGold(), 1, 1, TEXT_COLOR::WHILE, 1005.0f, 705.0f, 1.0f);
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
				if (m_Map[i][j - 1] == WALL) {
					Room *room = new Room(WALL_ROOM, Vector2(i, j), translation, WALL);
					AddRoom(room);
				} 
				else {
					Room *room = new Room(BORDER_ROOM, Vector2(i, j), translation, WALL);
					AddRoom(room);
				}
				
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
		for (auto& obj : m_InRangeRoom) {
				obj->Render(this->m_Camera);
		}
	}

	//RENDER TRAP
	for (auto& obj : m_InRangeTrap) {
		
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

	//RENDER UI
	{
		m_HpHolder->Render(m_Camera);
		m_HpBar->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_HpText);

		m_MpHolder->Render(m_Camera);
		m_MpBar->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_MpText);

		m_GoldIcon->Render(m_Camera);
		Renderer::GetInstance()->DrawText2(m_GoldText);

		m_ButtonPause->Render(m_Camera);
		if (m_isPause) {
			m_PauseBox->Render(m_Camera);
			m_ButtonResume->Render(m_Camera);
			m_ButtonQuit->Render(m_Camera);
		}

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
	if (m_isPause) {
		m_PauseBox->Update(frameTime);
		m_ButtonResume->Update(frameTime);
		m_ButtonQuit->Update(frameTime);

		UpdateControlPause(frameTime);
	}
	else {
		if (!m_isStartUp) {
			RoomsGenerate();
			m_iHandleBGM = SoundEngine::GetInstance()->Play(11, 0.25f, 1.0f, true);
			m_isStartUp = true;
		}
		
		Remove();

		UpdateInRange();
		

		UpdateRoomID();
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

	

	
		m_GoldIcon->Update(frameTime);
		m_GoldText->setText(m_Player->GetGold());
	}

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);
}

void StatePlay::UpdateInRange()
{
	ClearInRange();

	for (auto& obj : m_RoomList) if (CheckInRange(obj->m_RoomID) == true) m_InRangeRoom.push_back(obj);
	for (auto& obj : m_EnemyList) if (CheckInRange(obj->m_RoomID) == true) m_InRangeEnemy.push_back(obj);
	for (auto& obj : m_DropList) if (CheckInRange(obj->m_RoomID) == true) m_InRangeDrop.push_back(obj);
	for (auto& obj : m_TrapList) if (CheckInRange(obj->m_RoomID) == true) m_InRangeTrap.push_back(obj);
	for (auto& obj : m_SkillList) if (CheckInRange(obj->m_RoomID) == true) m_InRangeSkill.push_back(obj);
}

void StatePlay::ClearInRange()
{
	m_InRangeRoom.clear();
	m_InRangeDrop.clear();
	m_InRangeEnemy.clear();
	m_InRangeSkill.clear();
	m_InRangeTrap.clear();
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

	for (auto& obj : m_InRangeEnemy) {

		{
			if (!CollisionManager::CheckCollision(obj, GetRoomByID(obj->m_RoomID, m_RoomList))) 
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

	//BUTTON PAUSE
	if (m_ButtonPause->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isPause = true;
		return;
	}
	if (m_ButtonPause->isPressed(this->m_Camera)) {
		return;
	}
	m_ButtonPause->isHover(this->m_Camera);
	
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
	
		if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
		{
			m_Player->Dash(frameTime);
		}
		
		
	}


void StatePlay::UpdateControlPause(float frameTime) {
	//Button Resume
	if (m_ButtonResume->isReleased(this->m_Camera)) {
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
			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			InputManager::GetInstance()->ResetInput();
			StateManager::GetInstance()->CloseState();
			return;
		}
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

bool StatePlay::CheckInRange(Vector2 roomID) {

	Vector2 currRoom = m_Player->m_RoomID;
	if (roomID.x < currRoom.x - 1 || roomID.x > currRoom.x + 1 ||
		roomID.y < currRoom.y - 1 || roomID.y > currRoom.y + 1)
		return false;
	else 
		return true;
}
void StatePlay::GetRenderOrder() {
	for (auto a : m_InRangeEnemy) {
		m_ObjectList.push_back(a);
	}
	m_ObjectList.push_back(m_Player);

	std::sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object *a, Object *b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) > (b->GetPosY() - b->m_fHeight));
	});
}

void StatePlay::RemoveEnemy(Enemy* enemy) {



	//enemy->getGold()->m_isDisplay = true;
	int id;
	for (int i = 0; i < m_EnemyList.size(); i++) {
		if (m_EnemyList[i] == enemy)  id = i;
	}

	delete m_EnemyList[id];
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
