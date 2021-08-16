#include "stdafx.h"
#include <algorithm>
#include <time.h>
#include "StateLogo.h"
#include "SoundEngine.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Renderer.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateLogo::StateLogo(void) {
	this->Init();
}

StateLogo::~StateLogo() {
	delete m_Background;
	delete m_Logo;
	delete m_TransitionScreen;
	delete m_Camera;
}

void StateLogo::Init() {

	FILE* dataFile;
	dataFile = fopen(FILE_S_LOGO, "r");

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
		fscanf(dataFile, "#LOGO\n");
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
		m_Logo = new Fader(strPrefab, Vector2(0.0f, 0.0f), translation, fadeTime, isFadeIn);
	}

	fclose(dataFile);

	m_TransitionScreen = NULL;

	m_iHandleLogoSFX = SoundEngine::GetInstance()->Play(LOGO_SFX, 1.0f, 1.0f, false);
}

void StateLogo::Render() {
	//GetRenderOrder();

	m_Background->Render(this->m_Camera);
	m_Logo->Render(this->m_Camera);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Render(this->m_Camera);
}

void StateLogo::Update(float frameTime) {
	m_Background->Update(frameTime);
	m_Logo->Update(frameTime);

	if (m_TransitionScreen != NULL)
		m_TransitionScreen->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);
}

void StateLogo::UpdateControl(float frameTime)
{
	static bool isWelcomeState = true;
	static float fNextStateFrame = 3.0f;

	//Play State
	if (isWelcomeState) {
		fNextStateFrame -= frameTime;

		if (fNextStateFrame < 1.0f && m_TransitionScreen == NULL) {
			Matrix translation;
			translation.SetTranslation(-m_Camera->GetViewScale().x / 2, m_Camera->GetViewScale().y / 2, 2.0f);
			m_TransitionScreen = new Fader(TRANSISTION, Vector2(0.0f, 0.0f), translation, 1.0f, 1.0f);

			SoundEngine::GetInstance()->Fader(m_iHandleLogoSFX, false, 1.0f);
		}

		if (fNextStateFrame < 0.0f) {
			SoundEngine::GetInstance()->StopAll();

			StateManager::GetInstance()->m_GameStateStack.pop_back();
			ResourceManager::GetInstance()->ResetInstance();
			ResourceManager::GetInstance()->Init(FILE_R_WELCOME);
			StateManager::GetInstance()->AddState(GS_STATE_WELCOME);
		}
	}
}

void StateLogo::GetRenderOrder() {}