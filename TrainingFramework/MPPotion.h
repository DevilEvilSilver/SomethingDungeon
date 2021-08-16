#pragma once
#include"Drop.h"

class MPPotion : public Drop {
private:
	int m_iValue; // number of mp of this potion

public:

	MPPotion();
	MPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value);
	~MPPotion();

	void Update(float frameTime);
	void Render(Camera* camera);

	int getValue();
};