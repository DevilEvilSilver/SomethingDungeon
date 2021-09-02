#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StateIntro.h"
#include "SoundEngine.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateIntro::StateIntro(void) {
	this->Init();
}

StateIntro::~StateIntro() {
	delete m_Background;
	delete m_ButtonStart;
	delete m_Camera;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
}

void StateIntro::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_INTRO);
	SoundEngine::GetInstance()->Init(FILE_SD_INTRO);

	//read data file
	FILE* dataFile;
	dataFile = fopen(FILE_S_INTRO, "r");

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

	m_isStartUp = false;
	m_isNextState = false;
	m_fNextStateFrame = 1.0f;
	m_TransitionScreen = NULL;
}

void StateIntro::Render() {
	//GetRenderOrder();

	m_Background->Render(this->m_Camera);
	m_ButtonStart->Render(this->m_Camera);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateIntro::Update(float frameTime) {
	if (!m_isStartUp) {
		m_iHandleBGM = SoundEngine::GetInstance()->Play(INTRO_BGM, 1.0f, 1.0f, true);

		m_isStartUp = true;
	}

	m_Background->Update(frameTime);
	m_ButtonStart->Update(frameTime);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);
}

void StateIntro::UpdateControl(float frameTime)
{
	//Button Quit
	if (m_ButtonStart->isReleased(this->m_Camera)) {
		SoundEngine::GetInstance()->Play(BUTTON_SFX, 1.0f, 1.0f, false);
		m_isNextState = true;
		m_ButtonStart->m_isAvailble = false;
	}
	m_ButtonStart->isPressed(this->m_Camera);
	m_ButtonStart->isHover(this->m_Camera);

	//Welcome State
	if (m_isNextState) {
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

			StateManager::GetInstance()->ClosenLoadState(GS_STATE_PLAY);
			return;
		}
	}
}

void StateIntro::GetRenderOrder() {}