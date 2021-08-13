#pragma once
#include "Character.h"

class Player : public Character {
public:

	enum PlayerState
	{
		P_DASH,
		P_SKILL
	};

	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();

	float DashCoolDown = 5.0f;
	float currDashCD = 0.0f;

	

	bool Dash(float frameTime);
	//skill
	bool CoolMove(float frameTime);
	
	

	void UpdatePlayer(float frameTime);
	void Render(Camera *camera);
};