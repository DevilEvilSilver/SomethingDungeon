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

	//delete m_ButtonItem1;
	//delete m_ButtonItem2;
	//delete m_ButtonItem3;

	//delete m_ItemName1;
	//delete m_ItemDescription1;
	//delete m_ItemPrice1;
	//delete m_ItemName2;
	//delete m_ItemDescription2;
	//delete m_ItemPrice2;
	//delete m_ItemName3;
	//delete m_ItemDescription3;
	//delete m_ItemPrice3;
	delete m_ItemGoldIcon;

	delete m_StatHP;
	delete m_StatMP;
	delete m_StatATK;
	delete m_StatDEF;
	delete m_PlayerGold;
	delete m_PlayerGoldIcon;

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
	m_PlayerGold = new Text(m_Player->GetGold(), SHADER_TEXT, FONT_BANK, TEXT_COLOR::WHILE, 1005.0f, 520.0f, 1.0f);

	m_isStartUp = false;
	m_isPLayState = false;
	m_fNextStateFrame = 1.0f;
	m_TransitionScreen = NULL;
}

void StateShop::Render() {
	m_Background->Render(this->m_Camera);
	m_ButtonStart->Render(this->m_Camera);

	//m_ButtonItem1->Render(this->m_Camera);
	//m_ButtonItem2->Render(this->m_Camera);
	//m_ButtonItem3->Render(this->m_Camera);

	//if (!strcmp(m_ButtonItem1->m_strState.c_str(), B_HOVER)) {
	//	Renderer::GetInstance()->DrawText2(m_ItemName1);
	//	Renderer::GetInstance()->DrawText2(m_ItemDescription1);
	//	m_ItemGoldIcon->Render(this->m_Camera);
	//}
	//if (!strcmp(m_ButtonItem2->m_strState.c_str(), B_HOVER)) {
	//	Renderer::GetInstance()->DrawText2(m_ItemName2);
	//	Renderer::GetInstance()->DrawText2(m_ItemDescription2);
	//	m_ItemGoldIcon->Render(this->m_Camera);
	//}
	//if (!strcmp(m_ButtonItem3->m_strState.c_str(), B_HOVER)) {
	//	Renderer::GetInstance()->DrawText2(m_ItemName3);
	//	Renderer::GetInstance()->DrawText2(m_ItemDescription3);
	//	m_ItemGoldIcon->Render(this->m_Camera);
	//}
	m_ItemGoldIcon->Render(this->m_Camera);
	Renderer::GetInstance()->DrawText2(m_StatHP);
	Renderer::GetInstance()->DrawText2(m_StatMP);
	Renderer::GetInstance()->DrawText2(m_StatATK);
	Renderer::GetInstance()->DrawText2(m_StatDEF);
	Renderer::GetInstance()->DrawText2(m_PlayerGold);
	m_PlayerGoldIcon->Render(this->m_Camera);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateShop::Update(float frameTime) {
	if (!m_isStartUp) {
		m_iHandleBGM = SoundEngine::GetInstance()->Play(SHOP_BGM, 1.0f, 1.0f, true);

		m_isStartUp = true;
	}

	UpdateControl(frameTime);

	m_Camera->Update(frameTime);

	m_Background->Update(frameTime);
	m_ButtonStart->Update(frameTime);

	m_ItemGoldIcon->Update(frameTime);

	m_StatHP->setText("HEALTH: " + m_Player->GetHP());
	m_StatMP->setText("MANA: " + m_Player->GetMP());
	m_StatATK->setText("ATTACK: " + std::to_string(m_Player->m_ATK));
	m_StatDEF->setText("DEFENCE: " + std::to_string(m_Player->m_DEF));
	m_PlayerGold->setText(m_Player->GetGold());
	m_PlayerGoldIcon->Update(frameTime);
	
	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);
}

void StateShop::UpdateControl(float frameTime)
{
	//Button Start
	if (m_ButtonStart->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isPLayState = true;
		m_ButtonStart->m_isAvailble = false;
	}
	m_ButtonStart->isPressed(this->m_Camera);
	m_ButtonStart->isHover(this->m_Camera);

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
			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();

			StateManager::GetInstance()->AddLoadState(GS_STATE_PLAY);
			return;
		}
	}
}

void StateShop::GetRenderOrder() {}