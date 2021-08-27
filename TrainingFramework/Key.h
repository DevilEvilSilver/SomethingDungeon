#pragma once
#include"Drop.h"

class Key : public Drop {
public:

	Key(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Key();

	void OnCollision();
};