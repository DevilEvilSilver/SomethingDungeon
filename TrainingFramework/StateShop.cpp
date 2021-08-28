#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StateShop.h"
#include "SoundEngine.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateShop::StateShop(void) {
	this->Init();
}

StateShop::~StateShop() {
	delete m_Background;
	delete m_ButtonStart;

	delete m_ButtonPause;
	delete m_PauseBox;
	delete m_ButtonResume;
	delete m_ButtonQuit;

	delete m_ButtonReset;
	delete m_ResetName;
	delete m_ResetDescription;
	delete m_ResetPrice;
	delete m_ItemKeyIcon;

	for (auto& object : m_ButtonItemList) {
		delete object;
	}
	m_ButtonItemList.clear();
	for (auto& object : m_ItemNameList) {
		delete object;
	}
	m_ItemNameList.clear();
	for (auto& object : m_ItemDescriptionList) {
		delete object;
	}
	m_ItemDescriptionList.clear();
	for (auto& object : m_ItemPriceList) {
		delete object;
	}
	m_ItemPriceList.clear();
	delete m_ItemGoldIcon;

	delete m_StatHP;
	delete m_StatMP;
	delete m_StatATK;
	delete m_StatDEF;
	delete m_PlayerGold;
	delete m_PlayerGoldIcon;
	delete m_PlayerKey;
	delete m_PlayerKeyIcon;

	delete m_Player;
	delete m_Camera;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
}

void StateShop::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_SHOP);
	SoundEngine::GetInstance()->Init(FILE_SD_SHOP);

	FILE* dataFile;
	dataFile = fopen(FILE_S_SHOP, "r");

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
	m_Camera = new Camera(0.0f, 0.0f, fLeft, fRight, fBottom, fTop, fNear, fFar, fMovingSpeed, fRotationSpeed);

	//Background
	{
		fscanf(dataFile, "#BACKGROUND\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
		m_Background = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Start Button
	{
		fscanf(dataFile, "#BUTTON_START\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonStart = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Item Gold Icon
	{
		fscanf(dataFile, "#ITEM_GOLD_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ItemGoldIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Item Key Icon
	{
		fscanf(dataFile, "#ITEM_KEY_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ItemKeyIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Player Gold Icon
	{
		fscanf(dataFile, "#PLAYER_GOLD_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_PlayerGoldIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Player Key Icon
	{
		fscanf(dataFile, "#PLAYER_KEY_ICON\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_PlayerKeyIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Button Reset
	{
		fscanf(dataFile, "#BUTTON_RESET\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonReset = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
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

	fclose(dataFile);

	//Player 
	Matrix translation;
	translation.SetTranslation(0.0f, 0.0f, 0.0f);
	m_Player = new Player(PLAYER, Vector2(0.0f, 0.0f), translation);

	//INIT TEXT STAT
	m_StatHP = new Text("HEALTH: " + m_Player->GetHP(), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 750.0f, 210.0f , 1.0f);
	m_StatMP = new Text("MANA: " + m_Player->GetMP(), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 750.0f, 280.0f, 1.0f);
	m_StatATK = new Text("ATTACK: " + std::to_string(m_Player->m_ATK), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 750.0f, 350.0f, 1.0f);
	m_StatDEF = new Text("DEFENCE: " + std::to_string(m_Player->m_DEF), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 750.0f, 420.f, 1.0f);
	m_PlayerGold = new Text(m_Player->GetGold(), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 1022.0f, 520.0f, 1.0f, TEXT_ALIGN::RIGHT);
	m_PlayerKey = new Text(m_Player->GetKey(), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 1022.0f, 490.0f, 1.0f, TEXT_ALIGN::RIGHT);

	m_ResetName = new Text(ITEM_NAME_RESET, SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 28.0f, 634.0f, 1.1f);
	m_ResetDescription = new Text(ITEM_DESCRIPTION_RESET, SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 28.0f, 662.0f, 0.8f);
	m_ResetPrice = new Text(std::to_string(ITEM_PRICE_RESET), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 842.0f, 690.0f, 1.0f, TEXT_ALIGN::RIGHT);

	//INIT ITEMS
	for (unsigned int i = 0; i < ITEM_SELL; i++) {
		GenerateItem();
	}
	m_ButtonItemList[0]->m_fCameraPosX = -13.8889f; m_ButtonItemList[0]->m_fCameraPosY = 1.1111f;
	m_ButtonItemList[1]->m_fCameraPosX = -7.7778f; m_ButtonItemList[1]->m_fCameraPosY = 1.1111f;
	m_ButtonItemList[2]->m_fCameraPosX = -1.6667f; m_ButtonItemList[2]->m_fCameraPosY = 1.1111f;

	//INIT LOGIC
	m_isStartUp = false;
	m_isPLayState = false;
	m_isQuit = false;
	m_fNextStateFrame = 1.0f;
	m_TransitionScreen = NULL;
}

void StateShop::GenerateItem() {
	unsigned int item = rand() % ITEM_COUNT + 1;
	std::string strButton, strName, strDescription, strPrice;
	
	switch (item) {
	case ITEM_HP:
		strButton = BUTTON_ITEM_HP;
		strName = ITEM_NAME_HP;
		strDescription = ITEM_DESCRIPTION_HP;
		strPrice = std::to_string(ITEM_PRICE_HP);
		break;
	case ITEM_MP:
		strButton = BUTTON_ITEM_MP;
		strName = ITEM_NAME_MP;
		strDescription = ITEM_DESCRIPTION_MP;
		strPrice = std::to_string(ITEM_PRICE_MP);
		break;
	case ITEM_ATK:
		strButton = BUTTON_ITEM_ATK;
		strName = ITEM_NAME_ATK;
		strDescription = ITEM_DESCRIPTION_ATK;
		strPrice = std::to_string(ITEM_PRICE_ATK);
		break;
	case ITEM_DEF:
	default:
		strButton = BUTTON_ITEM_DEF;
		strName = ITEM_NAME_DEF;
		strDescription = ITEM_DESCRIPTION_DEF;
		strPrice = std::to_string(ITEM_PRICE_DEF);
		break;
	}

	Matrix translation;
	translation.SetTranslation(0.0f, 0.0f, 1.0f);
	Button* button = new Button(strButton, Vector2(0.0f, 0.0f), translation);
	AddItemButton(button);

	Text* textName = new Text(strName, SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 28.0f, 634.0f, 1.1f);
	AddItemName(textName);

	Text* textDescription = new Text(strDescription, SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 28.0f, 662.0f, 0.8f);
	AddItemDescription(textDescription);

	Text* textPrice = new Text(strPrice, SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 842.0f, 690.0f, 1.0f, TEXT_ALIGN::RIGHT);
	AddItemPrice(textPrice);
}

void StateShop::Render() {
	m_Background->Render(this->m_Camera);
	m_ButtonStart->Render(this->m_Camera);	

	m_ButtonReset->Render(this->m_Camera);

	if (!strcmp(m_ButtonReset->m_strState.c_str(), B_HOVER) ||
		!strcmp(m_ButtonReset->m_strState.c_str(), B_PRESSED)) {
		Renderer::GetInstance()->DrawText2(m_ResetName);
		Renderer::GetInstance()->DrawText2(m_ResetDescription);
		Renderer::GetInstance()->DrawText2(m_ResetPrice);
		m_ItemKeyIcon->Render(this->m_Camera);
	}

	for (auto& obj : m_ButtonItemList)
	{
		obj->Render(this->m_Camera);
	}

	for (unsigned int i = 0; i < ITEM_SELL; i++) {
		if (!strcmp(m_ButtonItemList[i]->m_strState.c_str(), B_HOVER) ||
			!strcmp(m_ButtonItemList[i]->m_strState.c_str(), B_PRESSED)) {
			Renderer::GetInstance()->DrawText2(m_ItemNameList[i]);
			Renderer::GetInstance()->DrawText2(m_ItemDescriptionList[i]);
			Renderer::GetInstance()->DrawText2(m_ItemPriceList[i]);
			m_ItemGoldIcon->Render(this->m_Camera);
		}
	}

	Renderer::GetInstance()->DrawText2(m_StatHP);
	Renderer::GetInstance()->DrawText2(m_StatMP);
	Renderer::GetInstance()->DrawText2(m_StatATK);
	Renderer::GetInstance()->DrawText2(m_StatDEF);
	Renderer::GetInstance()->DrawText2(m_PlayerGold);
	m_PlayerGoldIcon->Render(this->m_Camera);
	Renderer::GetInstance()->DrawText2(m_PlayerKey);
	m_PlayerKeyIcon->Render(this->m_Camera);

	m_ButtonPause->Render(m_Camera);
	if (m_isPause) {
		m_PauseBox->Render(m_Camera);
		m_ButtonResume->Render(m_Camera);
		m_ButtonQuit->Render(m_Camera);
	}

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateShop::Update(float frameTime) {
	if (!m_isStartUp) {
		m_iHandleBGM = SoundEngine::GetInstance()->Play(SHOP_BGM, 1.0f, 1.0f, true);

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
			UpdateControl(frameTime);

			m_Camera->Update(frameTime);

			m_Background->Update(frameTime);
			m_ButtonStart->Update(frameTime);

			m_ItemGoldIcon->Update(frameTime);
			m_ItemKeyIcon->Update(frameTime);

			m_StatHP->setText("HEALTH: " + m_Player->GetHP());
			m_StatMP->setText("MANA: " + m_Player->GetMP());
			m_StatATK->setText("ATTACK: " + std::to_string(m_Player->m_ATK));
			m_StatDEF->setText("DEFENCE: " + std::to_string(m_Player->m_DEF));
			m_PlayerGold->setText(m_Player->GetGold());
			m_PlayerGoldIcon->Update(frameTime);
			m_PlayerKey->setText(m_Player->GetKey());
			m_PlayerKeyIcon->Update(frameTime);
		}
	}

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);
}

void StateShop::UpdateControl(float frameTime)
{
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

	//Button Start
	if (m_ButtonStart->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);

		m_isPLayState = true;

		m_ButtonStart->m_isAvailble = false;
		for (auto& obj : m_ButtonItemList) {
			obj->m_isAvailble = false;
		}
	}
	m_ButtonStart->isPressed(this->m_Camera);
	m_ButtonStart->isHover(this->m_Camera);

	//Button Reset
	if (m_ButtonReset->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);

		unsigned int itemPrice = std::stoi(m_ResetPrice->m_text);

		if (itemPrice <= m_Player->m_KEY) {
			m_Player->m_KEY -= itemPrice;

			//Delete old items
			for (auto& object : m_ButtonItemList) {
				delete object;
			}
			m_ButtonItemList.clear();
			for (auto& object : m_ItemNameList) {
				delete object;
			}
			m_ItemNameList.clear();
			for (auto& object : m_ItemDescriptionList) {
				delete object;
			}
			m_ItemDescriptionList.clear();
			for (auto& object : m_ItemPriceList) {
				delete object;
			}
			m_ItemPriceList.clear();

			//init new items
			for (unsigned int i = 0; i < ITEM_SELL; i++) {
				GenerateItem();
			}
			m_ButtonItemList[0]->m_fCameraPosX = -13.8889f; m_ButtonItemList[0]->m_fCameraPosY = 1.1111f;
			m_ButtonItemList[1]->m_fCameraPosX = -7.7778f; m_ButtonItemList[1]->m_fCameraPosY = 1.1111f;
			m_ButtonItemList[2]->m_fCameraPosX = -1.6667f; m_ButtonItemList[2]->m_fCameraPosY = 1.1111f;
		}
	}
	m_ButtonReset->isPressed(this->m_Camera);
	m_ButtonReset->isHover(this->m_Camera);

	//Button Buy
	for (unsigned int i = 0; i < ITEM_SELL; i++) {
		if (m_ButtonItemList[i]->isReleased(this->m_Camera)) {
			SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
			
			UpdateItemLogic(i);
		}
		m_ButtonItemList[i]->isPressed(this->m_Camera);
		m_ButtonItemList[i]->isHover(this->m_Camera);
	}

	//Play State
	if (m_isPLayState) {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);

			SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 0) {
			SetRecord();

			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();

			StateManager::GetInstance()->ClosenLoadState(GS_STATE_PLAY);
			return;
		}
	}
}

void StateShop::UpdatePause(float frameTime) {
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

	//Quit
	if (m_isQuit) {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);

			SoundEngine::GetInstance()->Fader(m_iHandleBGM, false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 0) {
			SetRecord();

			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();
			InputManager::GetInstance()->ResetInput();

			StateManager::GetInstance()->CloseState();
			return;
		}
	}
}

void StateShop::UpdateItemLogic(unsigned int itemIndex) {
	unsigned int itemPrice = std::stoi(m_ItemPriceList[itemIndex]->m_text);

	if (itemPrice <= m_Player->m_GOLD) {
		m_Player->m_GOLD -= itemPrice;

		if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_HP)) {
			m_Player->m_currHP += 50;
			m_Player->m_maxHP += 50;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_MP)) {
			m_Player->m_currMP += 50;
			m_Player->m_maxMP += 50;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ATK)) {
			m_Player->m_ATK += 3;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_DEF)) {
			m_Player->m_DEF += 1;
		}

		m_ButtonItemList[itemIndex]->m_isAvailble = false;
	}
}

void StateShop::SetRecord() {
	FILE* recordFile;

	//read
	recordFile = fopen(FILE_RECORD, "r");
	char strFloor[50];
	fscanf(recordFile, "%s\n", &strFloor);
	fclose(recordFile);

	//write
	recordFile = fopen(FILE_RECORD, "w");

	fprintf(recordFile, "%s\n", strFloor);
	fprintf(recordFile, "CurrHP %d\n", m_Player->m_currHP);
	fprintf(recordFile, "MaxHP %d\n", m_Player->m_maxHP);
	fprintf(recordFile, "CurrMP %d\n", m_Player->m_currMP);
	fprintf(recordFile, "MaxMP %d\n", m_Player->m_maxMP);
	fprintf(recordFile, "ATK %d\n", m_Player->m_ATK);
	fprintf(recordFile, "DEF %d\n", m_Player->m_DEF);
	fprintf(recordFile, "Gold %d\n", m_Player->m_GOLD);
	fprintf(recordFile, "Key %d\n", INIT_PLAYER_KEY);

	fclose(recordFile);
}

void StateShop::AddItemButton(Button* button)
{
	m_ButtonItemList.push_back(button);
}
void StateShop::AddItemName(Text* name) {
	m_ItemNameList.push_back(name);
}
void StateShop::AddItemDescription(Text* description) {
	m_ItemDescriptionList.push_back(description);
}
void StateShop::AddItemPrice(Text* price) {
	m_ItemPriceList.push_back(price);
}

void StateShop::GetRenderOrder() {}