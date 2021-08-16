#include "stdafx.h"
#include <thread>
#include "StateManager.h"
#include "ResourceManager.h"
#include "define.h"

//include all STATEs here:
#include "StateTest.h"
#include "StateLoad.h"
#include "StateLogo.h"
#include "StateWelcome.h"
#include "SceneManager.h"

StateManager::StateManager()
{
	AddState(GS_STATE_LOGO);
}

StateManager::~StateManager() {
	//reset all state here
	StateTest::GetInstance()->ResetInstance();
	StateLoad::GetInstance()->ResetInstance();
	StateLogo::GetInstance()->ResetInstance();
	StateWelcome::GetInstance()->ResetInstance();
	SceneManager::GetInstance()->ResetInstance();
	//......
}

void StateManager::Update(float frameTime) {
	switch (m_GameStateStack.back()) {
	case GS_STATE_LOAD:
		StateLoad::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_LOGO:
		StateLogo::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_PLAY:
		SceneManager::GetInstance()->Update(frameTime);
		break;
	}
}

void StateManager::Render()
{
	switch (m_GameStateStack.back()) {
	case GS_STATE_LOAD:

		StateLoad::GetInstance()->Render();
		break;
	case GS_STATE_LOGO:
		StateLogo::GetInstance()->Render();
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance()->Render();
		break;
	case GS_STATE_PLAY:
		SceneManager::GetInstance()->Render();
		break;
	}
}

void StateManager::AddLoadState(GameState addedState) {
	m_GameStateStack.push_back(addedState);
	m_GameStateStack.push_back(GS_STATE_LOAD);
	StateLoad::GetInstance()->LoadNewState(addedState);
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





