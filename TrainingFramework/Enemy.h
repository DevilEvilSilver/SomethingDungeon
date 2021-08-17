#pragma once
#include "Character.h"
#include"Gold.h"

class Enemy : public Character {
private:
	Gold* m_gold;
	int m_inumGold;	

	
public:

	/////////////////////////////////////////////////
	
	//AI
	void UniqueUpdate(float frameTime);

	//DROP
	bool isDead ;

	//OPTION
	void Chase(Vector2 delta);
	void KeepDistance(Vector2 delta);

	//SKILL
	//--------------skill here----------------

    //----------------------------------------
	
	void Death(float frameiIme);
	////////////////////////////////////////////////
	

	//OTHER
	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();



	void setGold(Gold* gold) { m_gold = gold; }
	Gold* getGold() {return m_gold;}
	void createGoldObject();
};