#pragma once
#include <vector>


class StateManager {
private:
	static StateManager* s_Instance;

	

public:
	enum GameState {
<<<<<<< Updated upstream
		GS_WELCOME,
		GS_STAGE
	};

=======
		GS_STATE_1,
		GS_STATE_2,
		GS_STATE_3
	};

	int state = 0;

>>>>>>> Stashed changes
	
	std::vector<GameState> m_GameStateStack;	

	StateManager();
	~StateManager();

	void Update(float frameTime);
	
<<<<<<< Updated upstream
=======
	void Render();
>>>>>>> Stashed changes

	void AddState(GameState addedState);

	static StateManager* GetInstance();
	static void ResetInstance();
<<<<<<< Updated upstream
};
=======

	};
>>>>>>> Stashed changes
