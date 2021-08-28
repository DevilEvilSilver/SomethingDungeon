#pragma once
#include"Trap.h"
#include"Player.h"

class Gate : public Trap {
public:
	bool m_isCollide;

	float m_fTotalCoolDownTime = 2.0f;
	float m_fCurrCD = 0.0f;

	Gate();
	Gate(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Gate();

	void Update(float frameTime);

	bool CheckAvailable(Player *player);
};