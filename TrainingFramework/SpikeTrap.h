#pragma once
#include"Trap.h"
#include"Player.h"

class SpikeTrap : public Trap {
private:
	int m_iAttack=3;

public:
	float m_fTotalCoolDownTime;


	SpikeTrap();
	SpikeTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~SpikeTrap();

	void Update(float frameTime);
	

	int getValueAttack();
};