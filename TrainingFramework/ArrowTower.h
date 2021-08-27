#pragma once
#include"Trap.h"
#include "Player.h"

class ArrowTower : public Trap {
private:
	float currCD = 0;

public:


	ArrowTower();
	ArrowTower(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~ArrowTower();

	void Update(float frameTime);
	

	void createArrow();
};