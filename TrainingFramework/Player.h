#pragma once
#include "Character.h"
#include "Text.h"
#include"Gold.h"

class Player : public Character {
private:
	
public:
	Text* numGoldText;
	int m_inumGold;
	Text* numHPText;
	int m_iCurHP;


	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();

	void Update(float frameTime);
	void Render(Camera *camera);

	//tien add
	void increaseGold(Gold* gold);
	void increaseGold(int value);
	void increaseHP(int numHP);
};