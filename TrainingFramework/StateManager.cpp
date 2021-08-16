#include "stdafx.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "define.h"

//include all STATEs here:

#include "StateLogo.h"
#include "StateWelcome.h"
#include "StatePlay.h"

StateManager::StateManager()
{
	AddState(GS_STATE_LOGO);
	ResourceManager::GetInstance()->Init(FILE_R_LOGO);
}

StateManager::~StateManager() {
	//reset all state here
	
	StateLogo::GetInstance()->ResetInstance();
	StateWelcome::GetInstance()->ResetInstance();
	StatePlay::GetInstance()->ResetInstance();
	//......
}

void StateManager::Update(float frameTime) {



	
	switch (m_GameStateStack.back()) {
	case GS_STATE_LOGO:
		StateLogo::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_PLAY:
		StatePlay::GetInstance()->Update(frameTime);
		break;
	}
}

void StateManager::Render()
{
	switch (m_GameStateStack.back()) {
	case GS_STATE_LOGO:
		StateLogo::GetInstance()->Render();
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance()->Render();
		break;
	case GS_STATE_PLAY:
		StatePlay::GetInstance()->Render();
		break;
	}
}

void StateManager::AddState(GameState addedState)
{
	m_GameStateStack.push_back(addedState);

	if (addedState == GS_STATE_PLAY) StatePlay::GetInstance()->RoomsGenerate();
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





