#pragma once
#include <vector>


class StateManager {
private:
	static StateManager* s_Instance;

	

public:
	enum GameState {
		GS_WELCOME,
		GS_STAGE
	};

	
	std::vector<GameState> m_GameStateStack;	

	StateManager();
	~StateManager();

	void Update(float frameTime);
	

	void AddState(GameState addedState);

	static StateManager* GetInstance();
	static void ResetInstance();
};