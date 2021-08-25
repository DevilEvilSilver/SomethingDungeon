#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StateLoad.h"
#include "SoundEngine.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "define.h"

//all State
#include "StateLogo.h"
#include "StateWelcome.h"
#include "StatePlay.h"
#include "StateResult.h"

#define _CRT_SECURE_NO_WARNINGS

template <class T>
void EraseHead(std::vector<T> objList) {
	if (objList[0] != NULL)
		delete objList[0];
	objList.erase(objList.begin());
	objList.shrink_to_fit();
}


StateLoad::StateLoad(void) {
	this->Init();
}

StateLoad::~StateLoad() {
	delete m_Background;
	delete m_LoadIcon;
	delete m_Camera;

	if (m_TransitionScreen != NULL)
		delete m_TransitionScreen;
}

void StateLoad::Init() {
	ResourceManager::GetInstance()->Init(FILE_R_LOAD);
	SoundEngine::GetInstance()->Init(FILE_SD_LOAD);

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

	//Start Button
	{
		fscanf(dataFile, "#LOAD_ICON\n");
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);
		GLfloat x, y;
		fscanf(dataFile, "POS %f, %f\n", &x, &y);
		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);
		float fadeTime;
		fscanf(dataFile, "FADE_TIME %f\n", &fadeTime);
		unsigned int isFadeIn;
		fscanf(dataFile, "IS_FADE_IN %d\n", &isFadeIn);
		Matrix translation;
		translation.SetTranslation(x, y, 1.0f);
		m_LoadIcon = new Widget(strPrefab, Vector2(0.0f, 0.0f), translation);
	}

	fclose(dataFile);

	m_isNextState = false;
	m_fNextStateFrame = 1.0f;
	m_fStartUpFrame = 0.2f;
	m_TransitionScreen = NULL;
}

void StateLoad::Render() {
	//GetRenderOrder();

	m_Background->Render(this->m_Camera);
	m_LoadIcon->Render(this->m_Camera);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateLoad::Update(float frameTime) {
	m_Background->Update(frameTime);
	m_LoadIcon->Update(frameTime);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);

	if (!m_isNextState) {
		m_fStartUpFrame -= frameTime;

		if (m_fStartUpFrame <= 0.0f)
			LoadState();
	}
}

void StateLoad::UpdateControl(float frameTime)
{
	//Play State
	if (m_isNextState) {
		m_fNextStateFrame -= frameTime;

		if (m_fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);
		}

		if (m_fNextStateFrame < 0.0f) {
			SoundEngine::GetInstance()->StopAll();
			InputManager::GetInstance()->ResetInput();
			//ResetResource();   //error

			StateManager::GetInstance()->CloseState();
			return;
		}
	}
}

void StateLoad::LoadState() {
	switch (m_NextState) {
	case GS_STATE_LOGO:
		StateLogo::GetInstance();
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance();
		break;
	case GS_STATE_PLAY:
		StatePlay::GetInstance();
		break;
	case GS_STATE_RESULT:
		StateResult::GetInstance();
		break;
	}

	m_isNextState = true;
}

void StateLoad::GetRenderOrder() {}

void StateLoad::ResetResource() {
	for (int i = 0; i < 3; i++) {
		EraseHead(ResourceManager::GetInstance()->m_PrefabList);
	}
	for (int i = 0; i < 1; i++) {
		EraseHead(ResourceManager::GetInstance()->m_ModelList);
	}
	for (int i = 0; i < 2; i++) {
		EraseHead(ResourceManager::GetInstance()->m_ShaderList);
	}
}