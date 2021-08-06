#pragma once
#include "Character.h"

class Enemy : public Character {
public:


	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();

	void Update(float frameTime);
	void Render(Camera *camera);
};