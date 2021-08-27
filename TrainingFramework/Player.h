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

	//ENUM
	enum MoveDir {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	//STATS
	int m_GOLD;

	//STATE
	CharacterState m_pState;

	void UniqueUpdate(float frameTime);
	void Attack(float frameTime);
	//PLAYER SKILL
	virtual void UseSkill(float frameTime);
	virtual void AddSkill(std::string prefabId);
	virtual void UpdateChangeSkill(float frameTime); // change current skill
	bool Dash(float frameTime);
	//Update CoolDownTime
	virtual void UpdateCurrentCDTime(float frameTime);
	//FUNCT TO MOVE
	void PlayerMove(MoveDir dir);

	//CHANGE STATE

	//OTHER
	Player();
	Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Player();
	
	virtual void UseAttack();
	void LoadData();

	//UI
	std::string GetHP();
	std::string GetMP();
	std::string GetGold();
};
