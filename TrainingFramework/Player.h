#pragma once

#include "Player.h"

//#include "Skill.h"
class Player : public Character {
public:

	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();
	virtual void Attack(int x, int y);
	void Update(float frameTime);
	void Render(Camera *camera);
};