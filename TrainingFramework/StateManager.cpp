#include "stdafx.h"
#include "StateManager.h"
#include "SceneManager.h"
#include "define.h"

//include all STATEs here:
#include "StateTest.h"

StateManager::StateManager()
{
	AddState(GS_STATE_1);
	SceneManager::GetInstance()->RoomsGenerate();
}

StateManager::~StateManager() {
	//reset all state here
	StateTest::GetInstance()->ResetInstance();
	SceneManager::GetInstance()->ResetInstance();
	//......
}

void StateManager::Update(float frameTime) {



	
	switch (m_GameStateStack.back()) {
	case GS_STATE_1:
		SceneManager::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_2:
		StateTest::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_3:
		StateTest::GetInstance()->Update(frameTime);
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
		StateTest::GetInstance()->Render();
		break;
	case GS_STATE_3:
		StateTest::GetInstance()->Render();
		break;
	}
}

void StateManager::AddState(GameState addedState)
{
	m_GameStateStack.push_back(addedState);
}

void StateManager::CloseState()
{
	m_GameStateStack.pop_back();
}

void StateManager::ClosenAddState(GameState addedState)
{
	CloseState();
	AddState(addedState);
}





