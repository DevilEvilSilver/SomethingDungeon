#pragma once
#include "Character.h"
#include "Text.h"
#include"Gold.h"
#include "HPPotion.h"

#include "Player.h"

//#include "Skill.h"
class Player : public Character {
private:
	std::vector<SkillID*> m_UniqueSkillList;
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
	int m_GOLD;

	//STATE
	PlayerState m_pState;

	void UniqueUpdate(float frameTime);
	void Attack(float frameTime);
	//PLAYER SKILL
	virtual void UseSkill(float frameTime);
	virtual void AddSkill(std::string prefabId);
	virtual void UpdateChangeSkill(float frameTime); // change current skill\
	//Update CoolDownTime
	virtual void UpdateCurrentCDTime(float frameTime);
	//FUNCT TO MOVE
	void PlayerMove(MoveDir dir);

	//CHANGE STATE

	//OTHER
	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();
	
	//UI
	std::string GetHP();
	std::string GetMP();
	std::string GetGold();
};
