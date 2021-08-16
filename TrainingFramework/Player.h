#pragma once
#include "Character.h"
#include "Text.h"
#include"Gold.h"
#include "HPPotion.h"


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
	void UpdateCollideGold(float frameTime, Gold * gold);
	void UpdateCollideHP(float frameTime, HPPotion* hp);
	//void UpdateCollideSpikeTrap(float frameTime, SpikeTrap* trap);
	void Render(Camera *camera);

	//tien add
	void increaseGold(Gold* gold);
	void increaseGold(int value);
	void increaseHP(int numHP);
};