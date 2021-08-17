#pragma once
#include "Character.h"
#include "Text.h"
#include"Gold.h"
#include "HPPotion.h"

#include "Player.h"

//#include "Skill.h"
class Player : public Character {
private:
	
public:
	Text* numGoldText;
	Text* numHPText;
	Text* numMPText;

	//ENUM
	enum MoveDir {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	enum PlayerState
	{
		P_CS,
		P_DASH,
		P_SKILL//HERE
	};

	//STATS
	 int m_maxMP,
		m_currMP,
		m_GOLD;

	//STATE
	PlayerState m_pState;

	//PLAYER SKILL
	//---------------skill here---------------
	float DashCoolDown = 2.0f;
	float currDashCD = 0.0f;


	//----------------------------------------

	////////////////////////////////////////////////////////////////////////

	void UniqueUpdate(float frameTime);

	//PLAYER SKILL
	//---------------skill here---------------
	bool Dash(float frameTime);
	bool CoolMove(float frameTime);
	//----------------------------------------

	///////////////////////////////////////////////////////////////////////

	//FUNCT TO MOVE
	void PlayerMove(MoveDir dir);

	//CHANGE STATE
	void SetPS(PlayerState newPS);

	//OTHER
	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();
	
	virtual void Attack(int x, int y);


	void UpdateCollideGold(float frameTime, Gold * gold);
	void UpdateCollideHP(float frameTime, HPPotion* hp);
	// void Render(Camera *camera);

	
};