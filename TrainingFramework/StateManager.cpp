#include "stdafx.h"
#include "StateManager.h"
#include "define.h"


#include "InputManager.h"

//include all STATEs here:
#include "State1.h"
#include "State2.h"
#include "State3.h"

#include "SceneManager.h"


#define _CRT_SECURE_NO_WARNINGS

StateManager * StateManager::s_Instance = NULL;



StateManager::StateManager()
{
	AddState(GS_STATE_1);
}

StateManager::~StateManager() {}


void StateManager::Update(float frameTime) {
	
	switch (m_GameStateStack.back()) {
	case GS_STATE_1:
		SceneManager::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_2:
		State2::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_3:
		State3::GetInstance()->Update(frameTime);
		break;
	}
}

void StateManager::Render()
{
	switch (m_GameStateStack.back()) {
	case GS_STATE_1:
		SceneManager::GetInstance()->Render();
		break;
	case GS_STATE_2:
		State2::GetInstance()->Render();
		break;
	case GS_STATE_3:
		State3::GetInstance()->Render();
		break;
	}
}

void StateManager::AddState(GameState addedState)
{
	m_GameStateStack.push_back(addedState);
}

StateManager* StateManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new StateManager();
	return s_Instance;
}

void StateManager::ResetInstance() {

	//reset all state here
	SceneManager::GetInstance()->ResetInstance();
	State2::GetInstance()->ResetInstance();
	State3::GetInstance()->ResetInstance();
	
	//......

	delete s_Instance;
	s_Instance = NULL;
}



