#pragma once
#include "Character.h"

class Enemy : public Character {
public:


	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};