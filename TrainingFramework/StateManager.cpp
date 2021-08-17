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
		CloseState(m_GameStateStack.back());
	}

	//switch (m_GameStateStack.back()) {
	//case GS_STATE_LOGO:
	//	StateLogo::GetInstance()->ResetInstance();
	//	break;
	//case GS_STATE_WELCOME:
	//	StateLogo::GetInstance()->ResetInstance();
	//	StateWelcome::GetInstance()->ResetInstance();
	//	break;
	//case GS_STATE_PLAY:
	//	/*StateLogo::GetInstance()->ResetInstance();
	//	StateWelcome::GetInstance()->ResetInstance();*/
	//	StatePlay::GetInstance()->ResetInstance();
	//	break;
	//}

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

void StateManager::CloseState(GameState closedState)
{
	switch (closedState) {
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
	m_GameStateStack.pop_back();
}

void StateManager::ClosenAddState(GameState closedState, GameState addedState)
{
	CloseState(closedState);
	AddState(addedState);
}





