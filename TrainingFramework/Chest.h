#pragma once
#include"Trap.h"

class Chest : public Trap {
private:
	//int m_iValue;

public:

	Chest(std::string prefabID, Vector2 roomID, Matrix translationMatrix,int value);
	~Chest();

	void OnCollision();
	void createDrop();
	void Update(float frameTime);
	//int getValue();
};