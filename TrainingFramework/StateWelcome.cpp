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
	delete m_Camera;
}

void StateWelcome::Init() {

	FILE* dataFile;
	dataFile = fopen(FILE_S_WELCOME, "r");

	//Background
	fscanf(dataFile, "#BACKGROUND\n");
	unsigned int id;
	fscanf(dataFile, "ID %d\n", &id);
	GLfloat x, y;
	fscanf(dataFile, "POS %f, %f\n", &x, &y);
	char strPrefab[50];
	fscanf(dataFile, "PREFAB %s\n", &strPrefab);
	Matrix translation;
	translation.SetTranslation(x, y, 0.0f);
	m_Background = new Object(strPrefab, Vector2(0.0f, 0.0f), translation);

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

	fclose(dataFile);

}

void StateWelcome::Render() {
	//GetRenderOrder();
	
	m_Background->Render(this->m_Camera);

}

void StateWelcome::Update(float frameTime) {
	m_Background->Update(frameTime);

	m_Camera->Update(frameTime);

	UpdateControl(frameTime);
}

void StateWelcome::UpdateControl(float frameTime)
{
	//STATE CHANGE
	if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
	{
		StateManager::GetInstance()->m_GameStateStack.pop_back();
		ResourceManager::GetInstance()->ResetInstance();
		ResourceManager::GetInstance()->Init(FILE_R_PLAY);
		StateManager::GetInstance()->AddState(GS_STATE_PLAY);

		//ResetInstance();
	}
}

void StateWelcome::GetRenderOrder() {}