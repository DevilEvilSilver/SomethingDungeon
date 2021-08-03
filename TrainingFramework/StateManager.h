#pragma once
#include <vector>


class StateManager {
private:
	static StateManager* s_Instance;
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

	static StateManager* GetInstance();
	static void ResetInstance();

};

