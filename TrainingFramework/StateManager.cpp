#include "stdafx.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "define.h"

//include all STATEs here:
#include "StateLoad.h"
#include "StateLogo.h"
#include "StateWelcome.h"
#include "StatePlay.h"
#include "StateShop.h"
#include "StateResult.h"
#include "StateInstruction.h"
#include "StateCredit.h"

StateManager::StateManager()
{
	//AddState(GS_STATE_PLAY);
	AddState(GS_STATE_WELCOME);
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
		StatePlay::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_SHOP:
		StateShop::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_RESULT:
		StateResult::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_INSTRUCTION:
		StateInstruction::GetInstance()->Update(frameTime);
		break;
	case GS_STATE_CREDIT:
		StateCredit::GetInstance()->Update(frameTime);
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
		StatePlay::GetInstance()->Render();
		break;
	case GS_STATE_SHOP:
		StateShop::GetInstance()->Render();
		break;
	case GS_STATE_RESULT:
		StateResult::GetInstance()->Render();
		break;
	case GS_STATE_INSTRUCTION:
		StateInstruction::GetInstance()->Render();
		break;
	case GS_STATE_CREDIT:
		StateCredit::GetInstance()->Render();
		break;
	}
}

void StateManager::AddState(GameState addedState)
{
	if (m_GameStateStack.size() > 0) {
		ResetState(m_GameStateStack.back());
	}
	m_GameStateStack.push_back(addedState);
}

void StateManager::AddLoadState(GameState addedState) {
	if (m_GameStateStack.size() > 0) {
		ResetState(m_GameStateStack.back());
	}
	m_GameStateStack.push_back(addedState);
	m_GameStateStack.push_back(GS_STATE_LOAD);

	StateLoad::GetInstance()->m_isNextState = addedState;
}

void StateManager::CloseState()
{
	ResetState(m_GameStateStack.back());
	m_GameStateStack.pop_back();
}

void StateManager::ClosenAddState(GameState addedState)
{
	CloseState();
	m_GameStateStack.push_back(addedState);

	if (addedState == GS_STATE_PLAY)
		StatePlay::GetInstance()->RoomsGenerate();
}

void StateManager::ClosenLoadState(GameState addedState)
{
	CloseState();
	m_GameStateStack.push_back(addedState);
	m_GameStateStack.push_back(GS_STATE_LOAD);

	StateLoad::GetInstance()->m_isNextState = addedState;
}

void StateManager::ResetState(GameState state) {
	switch (state) {
	case GS_STATE_LOAD:
		StateLoad::GetInstance()->ResetInstance();
		break;
	case GS_STATE_LOGO:
		StateLogo::GetInstance()->ResetInstance();
		break;
	case GS_STATE_WELCOME:
		StateWelcome::GetInstance()->ResetInstance();
		break;
	case GS_STATE_PLAY:
		StatePlay::GetInstance()->ResetInstance();
		break;
	case GS_STATE_SHOP:
		StateShop::GetInstance()->ResetInstance();
		break;
	case GS_STATE_RESULT:
		StateResult::GetInstance()->ResetInstance();
		break;
	case GS_STATE_INSTRUCTION:
		StateInstruction::GetInstance()->ResetInstance();
		break;
	case GS_STATE_CREDIT:
		StateCredit::GetInstance()->ResetInstance();
		break;
	}
}



