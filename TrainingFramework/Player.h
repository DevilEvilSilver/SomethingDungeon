#pragma once
#include "Character.h"

class Player : public Character {
public:

	enum MoveDir {
		UP, DOWN, LEFT, RIGHT
	};

	void Update(float frameTime);
	void PlayerMoveDirection(MoveDir dir);
	bool CoolMove(float frameTime);
	bool Dash(float frameTime);

	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();

	

	
	void Render(Camera *camera);
};