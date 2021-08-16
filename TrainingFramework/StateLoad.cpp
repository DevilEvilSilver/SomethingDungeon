#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include <thread>
#include "StateLoad.h"
#include "ResourceManager.h"
#include "SoundEngine.h"
#include "StateManager.h"
#include "StateLogo.h"
#include "StateWelcome.h"
#include "SceneManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateLoad::StateLoad(void) {
	this->Init();
}

StateLoad::~StateLoad() {
	delete m_Background;
	delete m_LoadingIcon;
	delete m_TransitionScreen;
	delete m_Camera;
}

void StateLoad::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_LOAD);

	FILE* dataFile;
	dataFile = fopen(FILE_S_LOAD, "r");

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
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 0.0f);
		m_Background = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	//Loading icon
	{
		fscanf(dataFile, "#LOAD_ICON\n");
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_LoadingIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	fclose(dataFile);

	m_TransitionScreen = NULL;

	m_isNextState = false;
}

void StateLoad::Render() {
	//GetRenderOrder();

	m_Background->Render(this->m_Camera);
	m_LoadingIcon->Render(this->m_Camera);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateLoad::Update(float frameTime) {
	m_Background->Update(frameTime);
	m_LoadingIcon->Update(frameTime);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);
}

void StateLoad::UpdateControl(float frameTime)
{
	static float fNextStateFrame = 1.0f;

	//Next State
	if (m_isNextState) {
		fNextStateFrame -= frameTime;

		if (fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);
		}

		if (fNextStateFrame < 0.0f) {
			SoundEngine::GetInstance()->StopAll();

			StateManager::GetInstance()->CloseState();
		}
	}
}

void StateLoad::GetRenderOrder() {}

void StateLoad::LoadNewState(GameState newState) {
	switch (newState) {
	case GS_STATE_LOGO:
		StateLogo::GetInstance();
		//ResourceManager::GetInstance()->Init(FILE_R_LOGO);
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance();
		//ResourceManager::GetInstance()->Init(FILE_R_WELCOME);
		break;
	case GS_STATE_PLAY:
		SceneManager::GetInstance();
		//ResourceManager::GetInstance()->Init(FILE_R_PLAY);
		break;
	}

	//Sleep(5000);

	StateLoad::GetInstance()->m_isNextState = true;
}