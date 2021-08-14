#pragma once
#include "Character.h"

class Enemy : public Character {
public:

	/////////////////////////////////////////////////
	
	//AI
	void UniqueUpdate(float frameTime);

	//OPTION
	void Chase(Vector2 delta);
	void KeepDistance(Vector2 delta);

	//SKILL
	//--------------skill here----------------

    //----------------------------------------
	
	////////////////////////////////////////////////
	

	//OTHER
	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();

};