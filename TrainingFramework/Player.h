#pragma once
#include "Character.h"

class Player : public Character {
public:

	enum MoveDir {
		UP, DOWN, LEFT, RIGHT
	};

	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();

	float DashCoolDown = 5.0f;
	float currDashCD = 0.0f;

	void PlayerMoveDirection(MoveDir dir);
	bool CoolMove(float frameTime);
	bool Dash(float frameTime);
	

	void Update(float frameTime);
	void Render(Camera *camera);
};