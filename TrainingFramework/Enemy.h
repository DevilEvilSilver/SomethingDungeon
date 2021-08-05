#pragma once
#include "Character.h"

class Enemy : public Character {
public:


	Enemy();
	Enemy(std::string prefabID, Matrix translationMatrix);
	~Enemy();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};