#pragma once
#include <vector>
#include "Singleton.h"

enum GameState {
		GS_STATE_LOAD,
		GS_STATE_LOGO,
		GS_STATE_WELCOME,
		GS_STATE_PLAY
};

class StateManager:public Singleton<StateManager> 
{

public:
	std::vector<GameState> m_GameStateStack;	

	StateManager();
	~StateManager();

	void Update(float frameTime);
	void Render();

	void AddLoadState(GameState addedState);
	void AddState(GameState addedState);
	void CloseState();
	void ClosenAddState(GameState addedState);

};

