#pragma once
#include <vector>
#include "Singleton.h"

class StateManager:public Singleton<StateManager> 
{

public:
	enum GameState {
		GS_STATE_1,
		GS_STATE_2,
		GS_STATE_3
	};
	std::vector<GameState> m_GameStateStack;	

	StateManager();
	~StateManager();

	void Update(float frameTime);
	void Render();

	void AddState(GameState addedState);
	void CloseState();
	void ClosenAddState(GameState addedState);

};

