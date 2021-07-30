#include "stdafx.h"
#include "StateManager.h"
#include "define.h"
<<<<<<< Updated upstream
=======

#include "InputManager.h"

//include all STATEs here:
#include "State1.h"
#include "State2.h"
#include "State3.h"



>>>>>>> Stashed changes
#define _CRT_SECURE_NO_WARNINGS

StateManager * StateManager::s_Instance = NULL;



StateManager::StateManager()
{
<<<<<<< Updated upstream
	AddState(GS_WELCOME);
=======
	AddState(GS_STATE_1);
>>>>>>> Stashed changes
}

StateManager::~StateManager() {}

<<<<<<< Updated upstream
void StateManager::Update(float frameTime) {

	switch (m_GameStateStack.back()) {
	case GS_WELCOME:
		break;
	case GS_STAGE:
		break;
	}
=======

void StateManager::Update(float frameTime) {
	
	switch (m_GameStateStack.back()) {
	case GS_STATE_1:
		printf("State 1\n");
		state = 1;
		State1::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_2:
		state = 2;
		printf("State 2\n");
		State2::GetInstance()->Update(frameTime);
	
		break;
	case GS_STATE_3:
		state = 3;
		printf("State 3\n");
		State3::GetInstance()->Update(frameTime);
		break;
	}
	
}

void StateManager::Render()
{
	
	switch (m_GameStateStack.back()) {
	case GS_STATE_1:
		State1::GetInstance()->Render();
		break;
	case GS_STATE_2:
		State2::GetInstance()->Render();
		break;
	case GS_STATE_3:
		State3::GetInstance()->Render();
		break;
	}
	
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======

	//reset all state here
	State1::GetInstance()->ResetInstance();
	//......

>>>>>>> Stashed changes
	delete s_Instance;
	s_Instance = NULL;
}



