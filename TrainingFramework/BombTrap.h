#pragma once
#include"Trap.h"
#include "Player.h"

class BombTrap : public Trap {
private:
	int m_iAttack;

public:
	float timeTillDelete;
	bool isCollide;

	BombTrap();
	BombTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value);
	~BombTrap();

	void Update(float frameTime);
	void UpdateCollideBombTrap(float frameTime,Player* m_Player);
	void Render(Camera* camera);

	int getValueAttack();
};