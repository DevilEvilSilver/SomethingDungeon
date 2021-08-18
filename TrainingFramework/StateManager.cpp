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
}

StateManager::~StateManager() {
	//reset all state here
	
	while (m_GameStateStack.size() > 0) {
		CloseState();
	}

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
	if (m_GameStateStack.size() > 0) {
		ResetState(m_GameStateStack.back());
	}
	m_GameStateStack.push_back(addedState);

	if (addedState == GS_STATE_PLAY) 
		StatePlay::GetInstance()->RoomsGenerate();
}

void StateManager::CloseState()
{
	ResetState(m_GameStateStack.back());
	m_GameStateStack.pop_back();
}

void StateManager::ClosenAddState(GameState addedState)
{
	CloseState();
	AddState(addedState);
}

void StateManager::ResetState(GameState state) {
	switch (state) {
	case GS_STATE_LOGO:
		StateLogo::GetInstance()->ResetInstance();
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance()->ResetInstance();
		break;
	case GS_STATE_PLAY:
		StatePlay::GetInstance()->ResetInstance();
		break;
	}
}



