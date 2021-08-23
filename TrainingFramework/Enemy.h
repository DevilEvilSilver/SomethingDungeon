#pragma once
#include "Character.h"
#include"Gold.h"

class Enemy : public Character {
private:

public:

	/////////////////////////////////////////////////
	
	//AI
	virtual void UniqueUpdate(float frameTime);

	//DROP
	bool isDead ;

	//OPTION
	void Chase(Vector2 delta);
	void KeepDistance(Vector2 delta);

	bool start = false;
	Vector2 ranDir = Vector2(0.0f, 0.0f);
	bool MoveRandom(float frameTime);


	//SKILL
	//--------------skill here----------------
	float currCD = 0.0f;
	virtual void Shoot(Vector2 target);
	virtual void Melee(Vector2 target);
    //----------------------------------------
	
	void Death(float frameiIme);
	////////////////////////////////////////////////
	

	//OTHER
	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();





	virtual void createDrop();
};