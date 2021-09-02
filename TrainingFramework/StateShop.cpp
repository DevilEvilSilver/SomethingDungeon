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
	delete m_StatSPEED;
	delete m_StatMELEE;
	delete m_StatRANGE;
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
	m_StatHP = new Text("HEALTH:" + m_Player->GetHP(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 183.0f , 1.0f);
	m_StatMP = new Text("MANA:" + m_Player->GetMP(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 226.0f, 1.0f);
	m_StatATK = new Text("ATTACK:" + std::to_string(m_Player->m_ATK) + " (MAX " + std::to_string(PLAYER_ATK_MAX) + ")", 
		SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 269.0f, 1.0f);
	m_StatDEF = new Text("DEFENCE:" + std::to_string(m_Player->m_DEF) + " (MAX " + std::to_string(PLAYER_DEF_MAX) + ")", 
		SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 312.0f, 1.0f);
	m_StatSPEED = new Text("SPEED:" + std::to_string(m_Player->m_MOVESPEED).
		substr(0, std::to_string(m_Player->m_MOVESPEED).find(".") + 3) + " (MAX " + std::to_string(PLAYER_SPEED_MAX) + ")", 
		SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 355.0f, 1.0f);
	m_StatMELEE = new Text("MELEE:" + m_Player->GetCloseSkillName(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 398.0f, 1.0f);
	m_StatRANGE = new Text("RANGE:" + m_Player->GetRangeSkillName(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 750.0f, 441.0f, 1.0f);
	m_PlayerGold = new Text(m_Player->GetGold(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 1022.0f, 520.0f, 1.0f, TEXT_ALIGN::RIGHT);
	m_PlayerKey = new Text(m_Player->GetKey(), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 1022.0f, 490.0f, 1.0f, TEXT_ALIGN::RIGHT);

	m_ResetName = new Text(ITEM_NAME_RESET, SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 28.0f, 634.0f, 1.1f);
	m_ResetDescription = new Text(ITEM_DESCRIPTION_RESET, SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 28.0f, 662.0f, 0.8f);
	m_ResetPrice = new Text(std::to_string(ITEM_PRICE_RESET), SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 842.0f, 690.0f, 1.0f, TEXT_ALIGN::RIGHT);

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
	//unsigned int item = ITEM_SOLAR_DESCEND;
	std::string strButton = BUTTON_ITEM_HEART_STONE,
		strName = ITEM_NAME_HEART_STONE,
		strDescription = ITEM_DESCRIPTION_HEART_STONE,
		strPrice = std::to_string(ITEM_PRICE_MANA_CRYSTAL);
	
	//srand(time(0));
	item = RandomItem();

	//item rate
	item = RandomItem();
	switch (item) {
	case ITEM_HEART_STONE:
		strButton = BUTTON_ITEM_HEART_STONE;
		strName = ITEM_NAME_HEART_STONE;
		strDescription = ITEM_DESCRIPTION_HEART_STONE;
		strPrice = std::to_string(ITEM_PRICE_HEART_STONE);
		break;
	case ITEM_MANA_CRYSTAL:
		strButton = BUTTON_ITEM_MANA_CRYSTAL;
		strName = ITEM_NAME_MANA_CRYSTAL;
		strDescription = ITEM_DESCRIPTION_MANA_CRYSTAL;
		strPrice = std::to_string(ITEM_PRICE_MANA_CRYSTAL);
		break;
	case ITEM_HERCULES_FIST:
		strButton = BUTTON_ITEM_HERCULES_FIST;
		strName = ITEM_NAME_HERCULES_FIST;
		strDescription = ITEM_DESCRIPTION_HERCULES_FIST;
		strPrice = std::to_string(ITEM_PRICE_HERCULES_FIST);
		break;
	case ITEM_ATHENA_SHIELD:
		strButton = BUTTON_ITEM_ATHENA_SHIELD;
		strName = ITEM_NAME_ATHENA_SHIELD;
		strDescription = ITEM_DESCRIPTION_ATHENA_SHIELD;
		strPrice = std::to_string(ITEM_PRICE_ATHENA_SHIELD);
		break;
	case ITEM_CODEX_GIGAS:
		strButton = BUTTON_ITEM_CODEX_GIGAS;
		strName = ITEM_NAME_CODEX_GIGAS;
		strDescription = ITEM_DESCRIPTION_CODEX_GIGAS;
		strPrice = std::to_string(ITEM_PRICE_CODEX_GIGAS);
		break;
	case ITEM_HERMES_SHOE:
		strButton = BUTTON_ITEM_HERMES_SHOE;
		strName = ITEM_NAME_HERMES_SHOE;
		strDescription = ITEM_DESCRIPTION_HERMES_SHOE;
		strPrice = std::to_string(ITEM_PRICE_HERMES_SHOE);
		break;
	case ITEM_TITAN_CHAIN:
		strButton = BUTTON_ITEM_TITAN_CHAIN;
		strName = ITEM_NAME_TITAN_CHAIN;
		strDescription = ITEM_DESCRIPTION_TITAN_CHAIN;
		strPrice = std::to_string(ITEM_PRICE_TITAN_CHAIN);
		break;
	case ITEM_ARES_BLADE:
		strButton = BUTTON_ITEM_ARES_BLADE;
		strName = ITEM_NAME_ARES_BLADE;
		strDescription = ITEM_DESCRIPTION_ARES_BLADE;
		strPrice = std::to_string(ITEM_PRICE_ARES_BLADE);
		break;
	case ITEM_LIFE_STONE:
		strButton = BUTTON_ITEM_LIFE_STONE;
		strName = ITEM_NAME_LIFE_STONE;
		strDescription = ITEM_DESCRIPTION_LIFE_STONE;
		strPrice = std::to_string(ITEM_PRICE_LIFE_STONE);
		break;
	case ITEM_OCEAN_SHARDS:
		strButton = BUTTON_ITEM_OCEAN_SHARDS;
		strName = ITEM_NAME_OCEAN_SHARDS;
		strDescription = ITEM_DESCRIPTION_OCEAN_SHARDS;
		strPrice = std::to_string(ITEM_PRICE_OCEAN_SHARDS);
		break;
	case ITEM_GIGANTIFICATION:
		strButton = BUTTON_ITEM_GIGANTIFICATION;
		strName = ITEM_NAME_GIGANTIFICATION;
		strDescription = ITEM_DESCRIPTION_GIGANTIFICATION;
		strPrice = std::to_string(ITEM_PRICE_GIGANTIFICATION);
		break;
	case ITEM_ARTEMIS_BLESSING:
		strButton = BUTTON_ITEM_ARTEMIS_BLESSING;
		strName = ITEM_NAME_ARTEMIS_BLESSING;
		strDescription = ITEM_DESCRIPTION_ARTEMIS_BLESSING;
		strPrice = std::to_string(ITEM_PRICE_ARTEMIS_BLESSING);
		break;
	case ITEM_BARBATOS_FAVOR:
		strButton = BUTTON_ITEM_BARBATOS_FAVOR;
		strName = ITEM_NAME_BARBATOS_FAVOR;
		strDescription = ITEM_DESCRIPTION_BARBATOS_FAVOR;
		strPrice = std::to_string(ITEM_PRICE_BARBATOS_FAVOR);
		break;
	case ITEM_AAMON_CONTRACT:
		strButton = BUTTON_ITEM_AAMON_CONTRACT;
		strName = ITEM_NAME_AAMON_CONTRACT;
		strDescription = ITEM_DESCRIPTION_AAMON_CONTRACT;
		strPrice = std::to_string(ITEM_PRICE_AAMON_CONTRACT);
		break;
	case ITEM_HEALTH_POTION:
		strButton = BUTTON_ITEM_HEALTH_POTION;
		strName = ITEM_NAME_HEALTH_POTION;
		strDescription = ITEM_DESCRIPTION_HEALTH_POTION;
		strPrice = std::to_string(ITEM_PRICE_HEALTH_POTION);
		break;
	case ITEM_MANA_POTION:
		strButton = BUTTON_ITEM_MANA_POTION;
		strName = ITEM_NAME_MANA_POTION;
		strDescription = ITEM_DESCRIPTION_MANA_POTION;
		strPrice = std::to_string(ITEM_PRICE_MANA_POTION);
		break;
	case ITEM_BLEEDING_FLOWER:
		strButton = BUTTON_ITEM_BLEEDING_FLOWER;
		strName = ITEM_NAME_BLEEDING_FLOWER;
		strDescription = ITEM_DESCRIPTION_BLEEDING_FLOWER;
		strPrice = std::to_string(ITEM_PRICE_BLEEDING_FLOWER);
		break;
	case ITEM_CORRUPTED_VINE:
		strButton = BUTTON_ITEM_CORRUPTED_VINE;
		strName = ITEM_NAME_CORRUPTED_VINE;
		strDescription = ITEM_DESCRIPTION_CORRUPTED_VINE;
		strPrice = std::to_string(ITEM_PRICE_CORRUPTED_VINE);
		break;
	case ITEM_ROTTEN_GINSENG:
		strButton = BUTTON_ITEM_ROTTEN_GINSENG;
		strName = ITEM_NAME_ROTTEN_GINSENG;
		strDescription = ITEM_DESCRIPTION_ROTTEN_GINSENG;
		strPrice = std::to_string(ITEM_PRICE_ROTTEN_GINSENG);
		break;
	case ITEM_TWILIGHT_BERRY:
		strButton = BUTTON_ITEM_TWILIGHT_BERRY;
		strName = ITEM_NAME_TWILIGHT_BERRY;
		strDescription = ITEM_DESCRIPTION_TWILIGHT_BERRY;
		strPrice = std::to_string(ITEM_PRICE_TWILIGHT_BERRY);
		break;
	case ITEM_KEY:
		strButton = BUTTON_ITEM_KEY;
		strName = ITEM_NAME_KEY;
		strDescription = ITEM_DESCRIPTION_KEY;
		strPrice = std::to_string(ITEM_PRICE_KEY);
		break;
	case ITEM_FLAME_SWORD:
		strButton = BUTTON_ITEM_FLAME_SWORD;
		strName = ITEM_NAME_FLAME_SWORD;
		strDescription = ITEM_DESCRIPTION_FLAME_SWORD;
		strPrice = std::to_string(ITEM_PRICE_FLAME_SWORD);
		break;
	case ITEM_PYRO_WAVE:
		strButton = BUTTON_ITEM_PYRO_WAVE;
		strName = ITEM_NAME_PYRO_WAVE;
		strDescription = ITEM_DESCRIPTION_PYRO_WAVE;
		strPrice = std::to_string(ITEM_PRICE_PYRO_WAVE);
		break;
	case ITEM_SOLAR_DESCEND:
		strButton = BUTTON_ITEM_SOLAR_DESCEND;
		strName = ITEM_NAME_SOLAR_DESCEND;
		strDescription = ITEM_DESCRIPTION_SOLAR_DESCEND;
		strPrice = std::to_string(ITEM_PRICE_SOLAR_DESCEND);
		break;
	case ITEM_ICE_ARROW:
		strButton = BUTTON_ITEM_ICE_ARROW;
		strName = ITEM_NAME_ICE_ARROW;
		strDescription = ITEM_DESCRIPTION_ICE_ARROW;
		strPrice = std::to_string(ITEM_PRICE_ICE_ARROW);
		break;
	case ITEM_GLACIAL_BLAST:
		strButton = BUTTON_ITEM_GLACIAL_BLAST;
		strName = ITEM_NAME_GLACIAL_BLAST;
		strDescription = ITEM_DESCRIPTION_GLACIAL_BLAST;
		strPrice = std::to_string(ITEM_PRICE_GLACIAL_BLAST);
		break;
	case ITEM_ABSOLUTE_ZERO:
		strButton = BUTTON_ITEM_ABSOLUTE_ZERO;
		strName = ITEM_NAME_ABSOLUTE_ZERO;
		strDescription = ITEM_DESCRIPTION_ABSOLUTE_ZERO;
		strPrice = std::to_string(ITEM_PRICE_ABSOLUTE_ZERO);
		break;
	}

	Matrix translation;
	translation.SetTranslation(0.0f, 0.0f, 1.0f);
	Button* button = new Button(strButton, Vector2(0.0f, 0.0f), translation);
	AddItemButton(button);

	Text* textName = new Text(strName, SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 28.0f, 634.0f, 1.1f);
	AddItemName(textName);

	Text* textDescription = new Text(strDescription, SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 28.0f, 662.0f, 0.8f);
	AddItemDescription(textDescription);

	Text* textPrice = new Text(strPrice, SHADER_TEXT, FONT_SOLID, TEXT_COLOR::WHILE, 842.0f, 690.0f, 1.0f, TEXT_ALIGN::RIGHT);
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
	Renderer::GetInstance()->DrawText2(m_StatSPEED);
	Renderer::GetInstance()->DrawText2(m_StatMELEE);
	Renderer::GetInstance()->DrawText2(m_StatRANGE);
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

			m_StatHP->setText("HEALTH:" + m_Player->GetHP());
			m_StatMP->setText("MANA:" + m_Player->GetMP());
			m_StatATK->setText("ATTACK:" + std::to_string(m_Player->m_ATK) + " (MAX " + std::to_string(PLAYER_ATK_MAX) + ")");
			m_StatDEF->setText("DEFENCE:" + std::to_string(m_Player->m_DEF) + " (MAX " + std::to_string(PLAYER_DEF_MAX) + ")");
			m_StatSPEED->setText("SPEED:" + std::to_string(m_Player->m_MOVESPEED).
				substr(0, std::to_string(m_Player->m_MOVESPEED).find(".") + 3) + " (MAX " + std::to_string(PLAYER_SPEED_MAX) + ")");
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
			if (UpdateItemLogic(i)) 
				SoundEngine::GetInstance()->Play(BUY_SUCCESS_SFX, 1.0f, 1.0f, false);
			else
				SoundEngine::GetInstance()->Play(BUY_FAIL_SFX, 1.0f, 1.0f, false);
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

bool StateShop::UpdateItemLogic(unsigned int itemIndex) {
	unsigned int itemPrice = std::stoi(m_ItemPriceList[itemIndex]->m_text);

	if (itemPrice <= m_Player->m_GOLD) {
		if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_HEART_STONE)) {
			m_Player->m_maxHP += 25;
			m_Player->m_currHP += 25;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_MANA_CRYSTAL)) {
			m_Player->m_maxMP += 25;
			m_Player->m_currMP += 25;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_HERCULES_FIST)) {
			m_Player->m_ATK += 1;
			if (m_Player->m_ATK > PLAYER_ATK_MAX)
				m_Player->m_ATK = PLAYER_ATK_MAX;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ATHENA_SHIELD)) {
			m_Player->m_DEF += 1;
			if (m_Player->m_DEF > PLAYER_DEF_MAX)
				m_Player->m_DEF = PLAYER_DEF_MAX;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_CODEX_GIGAS)) {
			unsigned int currMaxMP = m_Player->m_maxMP;
			m_Player->m_maxMP *= 1.2f;
			m_Player->m_currMP += m_Player->m_maxMP - currMaxMP;

			m_Player->m_maxHP *= 0.7f;
			if (m_Player->m_maxHP < 1)
				m_Player->m_maxHP = 1;
			if (m_Player->m_maxHP < m_Player->m_currHP) {
				m_Player->m_currHP = m_Player->m_maxHP;
			}
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_HERMES_SHOE)) {
			m_Player->m_MOVESPEED += 0.5;
			if (m_Player->m_MOVESPEED > PLAYER_SPEED_MAX)
				m_Player->m_MOVESPEED = PLAYER_SPEED_MAX;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_TITAN_CHAIN)) {
			m_Player->m_DEF += 2;
			if (m_Player->m_DEF > PLAYER_DEF_MAX)
				m_Player->m_DEF = PLAYER_DEF_MAX;

			m_Player->m_ATK -= 3;
			if (m_Player->m_ATK < PLAYER_ATK_MIN)
				m_Player->m_ATK = PLAYER_ATK_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ARES_BLADE)) {
			m_Player->m_ATK += 2;
			if (m_Player->m_ATK > PLAYER_ATK_MAX)
				m_Player->m_ATK = PLAYER_ATK_MAX;

			m_Player->m_DEF -= 3;
			if (m_Player->m_DEF < PLAYER_DEF_MIN)
				m_Player->m_DEF = PLAYER_DEF_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_LIFE_STONE)) {
			m_Player->m_maxHP += 15;
			m_Player->m_currHP += 15;

			m_Player->m_DEF += 1;
			if (m_Player->m_DEF > PLAYER_DEF_MAX)
				m_Player->m_DEF = PLAYER_DEF_MAX;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_OCEAN_SHARDS)) {
			m_Player->m_maxMP += 15;
			m_Player->m_currMP += 15;

			m_Player->m_DEF += 1;
			if (m_Player->m_DEF > PLAYER_DEF_MAX)
				m_Player->m_DEF = PLAYER_DEF_MAX;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_GIGANTIFICATION)) {
			m_Player->m_ATK += 5;
			if (m_Player->m_ATK > PLAYER_ATK_MAX)
				m_Player->m_ATK = PLAYER_ATK_MAX;

			m_Player->m_DEF = PLAYER_DEF_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ARTEMIS_BLESSING)) {
			unsigned int currMaxHP = m_Player->m_maxHP;
			m_Player->m_maxHP *= 1.25f;
			m_Player->m_currHP += m_Player->m_maxHP - currMaxHP;

			m_Player->m_MOVESPEED += 0.5;
			if (m_Player->m_MOVESPEED > PLAYER_SPEED_MAX)
				m_Player->m_MOVESPEED = PLAYER_SPEED_MAX;

			m_Player->m_maxMP *= 0.3f;
			if (m_Player->m_maxMP < 1)
				m_Player->m_maxMP = 1;
			if (m_Player->m_maxMP < m_Player->m_currMP) {
				m_Player->m_currMP = m_Player->m_maxMP;
			}
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_BARBATOS_FAVOR)) {
			m_Player->m_maxHP += 75;
			m_Player->m_currHP += 75;

			m_Player->m_DEF -= 1;
			if (m_Player->m_ATK < PLAYER_DEF_MIN)
				m_Player->m_ATK = PLAYER_DEF_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_AAMON_CONTRACT)) {
			m_Player->m_maxMP += 75;
			m_Player->m_currMP += 75;

			m_Player->m_ATK -= 1;
			if (m_Player->m_ATK < PLAYER_ATK_MIN)
				m_Player->m_ATK = PLAYER_ATK_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_HEALTH_POTION)) {
			m_Player->m_currHP += m_Player->m_maxHP * 0.5f;
			if (m_Player->m_maxHP < m_Player->m_currHP) {
				m_Player->m_currHP = m_Player->m_maxHP;
			}
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_MANA_POTION)) {
			m_Player->m_currMP += m_Player->m_maxMP * 0.5f;
			if (m_Player->m_maxMP < m_Player->m_currMP) {
				m_Player->m_currMP = m_Player->m_maxMP;
			}
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_BLEEDING_FLOWER)) {
			m_Player->m_currHP = m_Player->m_maxHP;
			
			m_Player->m_DEF -= 1;
			if (m_Player->m_DEF < PLAYER_DEF_MIN)
				m_Player->m_DEF = PLAYER_DEF_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_CORRUPTED_VINE)) {
			m_Player->m_currMP = m_Player->m_maxMP;

			m_Player->m_ATK -= 1;
			if (m_Player->m_ATK < PLAYER_ATK_MIN)
				m_Player->m_ATK = PLAYER_ATK_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ROTTEN_GINSENG)) {
			m_Player->m_currHP = m_Player->m_maxHP;

			m_Player->m_MOVESPEED -= 0.25;
			if (m_Player->m_MOVESPEED < PLAYER_SPEED_MIN)
				m_Player->m_MOVESPEED = PLAYER_SPEED_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_TWILIGHT_BERRY)) {
			m_Player->m_currMP = m_Player->m_maxMP;

			m_Player->m_MOVESPEED -= 0.25;
			if (m_Player->m_MOVESPEED < PLAYER_SPEED_MIN)
				m_Player->m_MOVESPEED = PLAYER_SPEED_MIN;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_KEY)) {
			m_Player->m_KEY++;
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_FLAME_SWORD)) {
			if (m_Player->GetCloseSkill() == SKILL_FIRE1)
				return false;
			m_Player->AddSkill(SKILL_FIRE1);
			m_StatMELEE->setText("MELEE:" + m_Player->GetCloseSkillName());
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_PYRO_WAVE)) {
			if (m_Player->GetCloseSkill() == SKILL_FIRE2)
				return false;
			m_Player->AddSkill(SKILL_FIRE2);
			m_StatMELEE->setText("MELEE:" + m_Player->GetCloseSkillName());
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_SOLAR_DESCEND)) {
			if (m_Player->GetCloseSkill() == SKILL_FIRE3)
				return false;
			m_Player->AddSkill(SKILL_FIRE3);
			m_StatMELEE->setText("MELEE:" + m_Player->GetCloseSkillName());
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ICE_ARROW)) {
			if (m_Player->GetRangeSkill() == SKILL_FREEZE1)
				return false;
			m_Player->AddSkill(SKILL_FREEZE1);
			m_StatRANGE->setText("RANGE:" + m_Player->GetRangeSkillName());
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_GLACIAL_BLAST)) {
			if (m_Player->GetRangeSkill() == SKILL_FREEZE2)
				return false;
			m_Player->AddSkill(SKILL_FREEZE2);
			m_StatRANGE->setText("RANGE:" + m_Player->GetRangeSkillName());
		}
		else if (!strcmp(m_ButtonItemList[itemIndex]->m_strPrefabID.c_str(), BUTTON_ITEM_ABSOLUTE_ZERO)) {
			if (m_Player->GetRangeSkill() == SKILL_FREEZE3)
				return false;
			m_Player->AddSkill(SKILL_FREEZE3);
			m_StatRANGE->setText("RANGE:" + m_Player->GetRangeSkillName());
		}

		m_Player->m_GOLD -= itemPrice;
		m_ButtonItemList[itemIndex]->m_isAvailble = false;
		return true;
	}
	else 
		return false;
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
	fprintf(recordFile, "Time %d\n", m_Player->m_iTmpTime);
	fprintf(recordFile, "Kills %d\n", m_Player->m_iTmpKill);
	fprintf(recordFile, "Golds %d\n", m_Player->m_iTmpGold);
	fprintf(recordFile, "CurrHP %d\n", m_Player->m_currHP);
	fprintf(recordFile, "MaxHP %d\n", m_Player->m_maxHP);
	fprintf(recordFile, "CurrMP %d\n", m_Player->m_currMP);
	fprintf(recordFile, "MaxMP %d\n", m_Player->m_maxMP);
	fprintf(recordFile, "ATK %d\n", m_Player->m_ATK);
	fprintf(recordFile, "DEF %d\n", m_Player->m_DEF);
	fprintf(recordFile, "Gold %d\n", m_Player->m_GOLD);
	fprintf(recordFile, "Key %d\n", INIT_PLAYER_KEY);
	fprintf(recordFile, "Speed %f\n", m_Player->m_MOVESPEED);
	fprintf(recordFile, "Melee %s\n", m_Player->GetCloseSkill().c_str());
	fprintf(recordFile, "Range %s\n", m_Player->GetRangeSkill().c_str());

	fclose(recordFile);
}

int StateShop::RandomItem()
{
	int item = 21;
	int randomNum = 1 + rand() % 100;
	if (randomNum <= 40)
	{
		//UPGRADE
		randomNum = 1 + rand() % 100;
		if (randomNum <= 40)
		{
			//Tier 1
			randomNum = 1 + rand() % 5;
			switch (randomNum)
			{
			case 1:
				item = 1;
				break;
			case 2:
				item = 2;
				break;
			case 3:
				item = 3;
				break;
			case 4:
				item = 4;
				break;
			case 5:
				item = 6;
				break;
			}

		}//tier 1
		else if (randomNum <= 70)
		{
			randomNum = 1 + rand() % 4;
			switch (randomNum)
			{
			case 1:
				item = 5;
				break;
			case 2:
				item = 12;
				break;
			case 3:
				item = 13;
				break;
			case 4:
				item = 14;
				break;
			}

		}//tier 2
		else if (randomNum <= 85)
		{
			randomNum = 1 + rand() % 3;
			switch (randomNum)
			{
			case 1:
				item = 7;
				break;
			case 2:
				item = 8;
				break;
			case 3:
				item = 12;
				break;
			}
		}//tier 3
		else if (randomNum <= 100)
		{
			randomNum = 1 + rand() % 3;
			switch (randomNum)
			{
			case 1:
				item = 9;
				break;
			case 2:
				item = 10;
				break;
			case 3:
				item = 11;
				break;
			}
		}//tier 4
	}//upgrade
	else if (randomNum <= 60)
	{
		//HEAL
		randomNum = 1 + rand() % 6;
		switch (randomNum)
		{
		case 1:
			item = 15;
			break;
		case 2:
			item = 16;
			break;
		case 3:
			item = 17;
			break;
		case 4:
			item = 18;
			break;
		case 5:
			item = 19;
			break;
		case 6:
			item = 20;
			break;
		}

	}//heal
	else if (randomNum <= 90)
	{
		//SKILL
		randomNum = 1 + rand() % 100;
		//if (randomNum <= 30)
		//{
		//	if (rand() % 100 >= 50) item = 22;
		//	else item = 25;
		//}else 
		if (randomNum <= 70)
		{
			if (rand() % 100 >= 50) item = 23;
			else item = 26;
		}
		else if (randomNum <= 100)
		{
			if (rand() % 100 >= 50) item = 24;
			else item = 27;
		}
	}//skill
	else if (randomNum <= 100)
	{
		//KEY
		item = 21;
	}//key

	return item;
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