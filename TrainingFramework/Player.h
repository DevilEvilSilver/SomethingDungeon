#pragma once
#include "Character.h"

class Player : public Character {
public:


	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();

	void Update(float frameTime);
	void Render(Camera *camera);
};