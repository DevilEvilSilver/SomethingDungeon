#include "stdafx.h"
#include "StateManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

StateManager * StateManager::s_Instance = NULL;



StateManager::StateManager()
{
	AddState(GS_WELCOME);
}

StateManager::~StateManager() {}

void StateManager::Update(float frameTime) {

	switch (m_GameStateStack.back()) {
	case GS_WELCOME:
		break;
	case GS_STAGE:
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
	delete s_Instance;
	s_Instance = NULL;
}



