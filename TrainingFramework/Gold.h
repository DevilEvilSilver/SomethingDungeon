#pragma once
#include"Drop.h"

class Gold : public Drop {
private:
	int m_iValue;

public:
	//bool m_isDisplay;

	Gold();
	Gold(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value, bool isDisplay);
	~Gold();

	void Update(float frameTime);
	void Render(Camera* camera);

	int getValue();
};