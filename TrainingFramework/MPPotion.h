#pragma once
#include"Drop.h"

class MPPotion : public Drop {
private:
	int m_iValue=5; // number of mp of this potion

public:


	MPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~MPPotion();

	void OnCollision();

	int getValue();
};