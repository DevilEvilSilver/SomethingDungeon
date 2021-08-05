#pragma once
#include "Character.h"

class Player : public Character {
public:


	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};