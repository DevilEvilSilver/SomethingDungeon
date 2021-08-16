#pragma once
#include"Drop.h"

class HPPotion : public Drop {
private:
	int m_iValue;

public:

	HPPotion();
	HPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value);
	~HPPotion();

	void Update(float frameTime);
	void Render(Camera* camera);

	int getValue();
};