#pragma once
#include"Drop.h"

class Gold : public Drop {
private:
	int m_iValue;

public:

	Gold(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value, bool isDisplay);
	~Gold();

	void OnCollision();

	int getValue();
};