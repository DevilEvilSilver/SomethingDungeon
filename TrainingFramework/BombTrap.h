#pragma once
#include"Trap.h"
#include "Player.h"

class BombTrap : public Trap {
private:
	int m_iAttack=3;

public:
	float timeTillDelete;
	bool isCollide;

	BombTrap();
	BombTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~BombTrap();

	void Update(float frameTime);
	void UpdateCollideBombTrap(float frameTime,Player* m_Player);




	int getValueAttack();
};