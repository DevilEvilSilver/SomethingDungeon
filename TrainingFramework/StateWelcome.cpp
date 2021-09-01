#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StateWelcome.h"
#include "SoundEngine.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateWelcome::StateWelcome(void) {
	this->Init();
}

StateWelcome::~StateWelcome() {
	delete m_Background;
	delete m_Title;
	delete m_ButtonContinue;
	delete m_ButtonStart;
	delete m_ButtonInstruction;
	delete m_ButtonCredit;
	delete m_Camera;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
}

void StateWelcome::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_WELCOME);
	SoundEngine::GetInstance()->Init(FILE_SD_WELCOME);

	// read file record
	FILE* recordFile;
	recordFile = fopen(FILE_RECORD, "r");

	char strisWin[50];
	fscanf(recordFile, "%s\n", &strisWin);
	if (strcmp(strisWin, RECORD_WIN) && 
		strcmp(strisWin, RECORD_LOSE))
		m_isContinueable = true;
	else 
		m_isContinueable = false;

	fclose(recordFile);

	//data file
	FILE* dataFile;
	dataFile = fopen(FILE_S_WELCOME, "r");

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

	//Title
	{
		fscanf(dataFile, "#TITLE\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
		m_Title = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Continue Button
	{
		fscanf(dataFile, "#BUTTON_CONTINUE\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonContinue = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
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

	//Instruction Button
	{
		fscanf(dataFile, "#BUTTON_INSTRUCTION\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonInstruction = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Credit Button
	{
		fscanf(dataFile, "#BUTTON_CREDIT\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_ButtonCredit = new Button(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	fclose(dataFile);

	m_isStartUp = false;
	m_isLoadData = false;
	m_isPLayState = false;
	m_isInstructionState = false;
	m_isCreditState = false;
	m_fNextStateFrame = 1.0f;
	m_TransitionScreen = NULL;
}

void StateWelcome::Render() {
	//GetRenderOrder();
	
	m_Background->Render(this->m_Camera);
	m_Title->Render(this->m_Camera);
	if (m_isContinueable)
		m_ButtonContinue->Render(this->m_Camera);
	m_ButtonStart->Render(this->m_Camera);
	m_ButtonInstruction->Render(this->m_Camera);
	m_ButtonCredit->Render(this->m_Camera);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateWelcome::Update(float frameTime) {
	if (!m_isStartUp) {
		m_iHandleBGM = SoundEngine::GetInstance()->Play(WELCOME_BGM, 1.0f, 1.0f, true);

		m_isStartUp = true;
	}

	m_Background->Update(frameTime);
	m_Title->Update(frameTime);
	if (m_isContinueable)
		m_ButtonContinue->Update(frameTime);
	m_ButtonStart->Update(frameTime);
	m_ButtonInstruction->Update(frameTime);
	m_ButtonCredit->Update(frameTime);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);
}

void StateWelcome::UpdateControl(float frameTime)
{
	//Button Continue
	if (m_ButtonContinue->isReleased(this->m_Camera) && m_isContinueable) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isLoadData = true;
		m_ButtonContinue->m_isAvailble = false;
		m_ButtonStart->m_isAvailble = false;
		m_ButtonInstruction->m_isAvailble = false;
		m_ButtonCredit->m_isAvailble = false;
	}
	m_ButtonContinue->isPressed(this->m_Camera);
	m_ButtonContinue->isHover(this->m_Camera);

	//Button Start
	if (m_ButtonStart->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isPLayState = true;
		m_ButtonContinue->m_isAvailble = false;
		m_ButtonStart->m_isAvailble = false;
		m_ButtonInstruction->m_isAvailble = false;
		m_ButtonCredit->m_isAvailble = false;
	}
	m_ButtonStart->isPressed(this->m_Camera);
	m_ButtonStart->isHover(this->m_Camera);

	//Button Instruction
	if (m_ButtonInstruction->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isInstructionState = true;
		m_ButtonContinue->m_isAvailble = false;
		m_ButtonStart->m_isAvailble = false;
		m_ButtonInstruction->m_isAvailble = false;
		m_ButtonCredit->m_isAvailble = false;
	}
	m_ButtonInstruction->isPressed(this->m_Camera);
	m_ButtonInstruction->isHover(this->m_Camera);

	//Button Credit
	if (m_ButtonCredit->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isCreditState = true;
		m_ButtonContinue->m_isAvailble = false;
		m_ButtonStart->m_isAvailble = false;
		m_ButtonInstruction->m_isAvailble = false;
		m_ButtonCredit->m_isAvailble = false;
	}
	m_ButtonCredit->isPressed(this->m_Camera);
	m_ButtonCredit->isHover(this->m_Camera);

	//Continue
	if (m_isLoadData) {
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

	//New game
	if (m_isPLayState) {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);

			SoundEngine::GetInstance()->Fader(m_iHandleBGM ,false, m_fNextStateFrame);
		}

		if (m_fNextStateFrame < 0) {
			InitRecord();

			SoundEngine::GetInstance()->StopAll();
			ResourceManager::GetInstance()->ResetInstance();
			SoundEngine::GetInstance()->ResetInstance();

			StateManager::GetInstance()->AddLoadState(GS_STATE_PLAY);
			return;
		}
	}

	//Instruction
	if (m_isInstructionState) {
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

			StateManager::GetInstance()->AddState(GS_STATE_INSTRUCTION);
			return;
		}
	}

	//Credit
	if (m_isCreditState) {
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

			StateManager::GetInstance()->AddState(GS_STATE_CREDIT);
			return;
		}
	}
}

void StateWelcome::InitRecord() {
	FILE* recordFile;
	recordFile = fopen(FILE_RECORD, "w");

	fprintf(recordFile, "%s\n", FLOOR_1);
	fprintf(recordFile, "CurrHP %d\n", INIT_PLAYER_HP);
	fprintf(recordFile, "MaxHP %d\n", INIT_PLAYER_HP);
	fprintf(recordFile, "CurrMP %d\n", INIT_PLAYER_MP);
	fprintf(recordFile, "MaxMP %d\n", INIT_PLAYER_MP);
	fprintf(recordFile, "ATK %d\n", INIT_PLAYER_ATK);
	fprintf(recordFile, "DEF %d\n", INIT_PLAYER_DEF);
	fprintf(recordFile, "Gold %d\n", INIT_PLAYER_GOLD);
	fprintf(recordFile, "Key %d\n", INIT_PLAYER_KEY);
	fprintf(recordFile, "Speed %f\n", INIT_PLAYER_SPEED);
	fprintf(recordFile, "Melee %s\n", INIT_PLAYER_MELEE);
	fprintf(recordFile, "Range %s\n", INIT_PLAYER_RANGE);

	fclose(recordFile);
}

void StateWelcome::GetRenderOrder() {}