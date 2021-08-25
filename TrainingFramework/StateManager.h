#pragma once
#include <vector>
#include "Singleton.h"
#include "StateBase.h"

enum GameState {
		GS_STATE_LOAD,
		GS_STATE_LOGO,
		GS_STATE_WELCOME,
		GS_STATE_PLAY,
		GS_STATE_SHOP,
		GS_STATE_RESULT
};

class StateManager:public Singleton<StateManager> 
{

public:
	std::vector<GameState> m_GameStateStack;	

	StateManager();
	~StateManager();

	void Update(float frameTime);
	void Render();

	void AddState(GameState addedState);
	void AddLoadState(GameState addedState);
	void CloseState();
	void ClosenAddState(GameState addedState);
	void ResetState(GameState addedState);

};

