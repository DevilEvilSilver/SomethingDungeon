#pragma once
#include"Trap.h"
#include"Player.h"

class SpikeTrap : public Trap {
private:
	int m_iAttack;

public:
	float m_fCoolDownTime;

	SpikeTrap();
	SpikeTrap(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value);
	~SpikeTrap();

	void Update(float frameTime);
	void UpdateCollideSpikeTrap(float frameTime, Player* player);
	void Render(Camera* camera);

	int getValueAttack();
};