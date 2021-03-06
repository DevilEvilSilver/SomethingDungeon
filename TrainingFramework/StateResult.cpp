#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StateResult.h"
#include "SoundEngine.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateResult::StateResult(void) {
	this->Init();
}

StateResult::~StateResult() {
	delete m_Background;
	delete m_ResultBox;
	delete m_Title;
	delete m_ButtonQuit;
	delete m_TotalTimeText;
	delete m_TotalKillText;
	delete m_TotalGoldText;
	delete m_Camera;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
}

void StateResult::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_RESULT);
	SoundEngine::GetInstance()->Init(FILE_SD_RESULT);

	// read file record
	FILE* recordFile;
	recordFile = fopen(FILE_RECORD, "r");

	char strisWin[50];
	fscanf(recordFile, "%s\n", &strisWin);
	if (!strcmp(strisWin, RECORD_WIN))
		m_isWin = true;
	else
		m_isWin = false;
	fscanf(recordFile, "Time %d\n", &m_TotalTime);
	fscanf(recordFile, "Kills %d\n", &m_TotalKill);
	fscanf(recordFile, "Golds %d\n", &m_TotalGold);

	fclose(recordFile);

	//read data file
	FILE* dataFile;
	dataFile = fopen(FILE_S_RESULT, "r");

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
		if (m_isWin) 
			m_Background = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation, WIN_BG);
		else 
			m_Background = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation, LOSE_BG);
	}

	//Result Box
	{
		fscanf(dataFile, "#RESULT_BOX\n");
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
		m_ResultBox = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
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
		if (m_isWin)
			m_Title = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation, WIN_TITLE);
		else 
			m_Title = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation, LOSE_TITLE);
	}

	//Quit Button
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

	//Init Text
	m_TotalTimeText = new Text("Time: " + GetTime(m_TotalTime), SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 540.0f, 380.0f, 1.0f, TEXT_ALIGN::CENTER);
	m_TotalKillText = new Text("Kills: " + std::to_string(m_TotalKill), SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 540.0f, 460.0f, 1.0f, TEXT_ALIGN::CENTER);
	m_TotalGoldText = new Text("Golds: " + std::to_string(m_TotalGold), SHADER_TEXT, FONT_BANK_BOLD, TEXT_COLOR::WHILE, 540.0f, 540.0f, 1.0f, TEXT_ALIGN::CENTER);

	m_isStartUp = false;
	m_isWelcomeState = false;
	m_fNextStateFrame = 1.0f;
	m_TransitionScreen = NULL;
}

std::string StateResult::GetTime(unsigned int second) {
	if ((int)(second % 60) < 10)
		return std::to_string((int)second / 60) + ":0" + std::to_string((int)second % 60);
	else
		return std::to_string((int)second / 60) + ":" + std::to_string((int)second % 60);
}

void StateResult::Render() {
	//GetRenderOrder();

	m_Background->Render(this->m_Camera);
	m_ResultBox->Render(this->m_Camera);
	m_Title->Render(this->m_Camera);
	m_ButtonQuit->Render(this->m_Camera);

	Renderer::GetInstance()->DrawText2(m_TotalTimeText);
	Renderer::GetInstance()->DrawText2(m_TotalKillText);
	Renderer::GetInstance()->DrawText2(m_TotalGoldText);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateResult::Update(float frameTime) {
	if (!m_isStartUp) {
		if (m_isWin) {
			m_iHandleBGM = SoundEngine::GetInstance()->Play(WIN_BGM, 1.0f, 1.0f, true);
		}
		else {
			m_iHandleBGM = SoundEngine::GetInstance()->Play(LOSE_BGM, 1.0f, 1.0f, true);
		}

		m_isStartUp = true;
	}

	m_Background->Update(frameTime);
	m_ResultBox->Update(frameTime);
	m_Title->Update(frameTime);
	m_ButtonQuit->Update(frameTime);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);
}

void StateResult::UpdateControl(float frameTime)
{
	//Button Quit
	if (m_ButtonQuit->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isWelcomeState = true;
		m_ButtonQuit->m_isAvailble = false;
	}
	m_ButtonQuit->isPressed(this->m_Camera);
	m_ButtonQuit->isHover(this->m_Camera);

	//Welcome State
	if (m_isWelcomeState) {
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

			StateManager::GetInstance()->CloseState();
			return;
		}
	}
}

void StateResult::GetRenderOrder() {}