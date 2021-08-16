#pragma once
#include"Drop.h"

class HPPotion : public Drop {
private:
	int m_iValue=3;

public:


	HPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~HPPotion();

	void OnCollision();

	int getValue();
};