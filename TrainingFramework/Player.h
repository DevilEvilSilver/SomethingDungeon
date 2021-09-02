#pragma once
#include "Character.h"
#include "Text.h"
#include"Gold.h"
#include "HPPotion.h"

#include "Player.h"

//#include "Skill.h"
class Player : public Character {
private:
	SkillID* m_RangeSkillID;
	SkillID* m_CloseSkillID;
	SkillID* m_Dash;
public:
	unsigned int m_iTmpTime;
	unsigned int m_iTmpKill;
	unsigned int m_iTmpGold;

	//ENUM
	enum MoveDir {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	//STATS
	int m_maxMP,
		m_currMP,
		m_GOLD,
		m_KEY;

	//STATE
	enum PlayerState
	{
		P_DASH,
		P_CS

	};
	
	PlayerState m_pState=P_CS;

	void UniqueUpdate(float frameTime);
	void Attack(float frameTime);
	//PLAYER SKILL
	virtual void UseSkill(float frameTime);
	virtual void AddSkill(std::string prefabId);
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

	std::string GetCloseSkill();
	std::string GetRangeSkill();
	std::string GetCloseSkillName();
	std::string GetRangeSkillName();
	float GetCloseSkillMaxCD();
	float GetRangeSkillMaxCD();
	float GetDashSkillMaxCD();
	float GetDashSkillCurrCD();
	float GetCloseSkillCurrCD();
	float GetRangeSkillCurrCD();
	std::string GetHP();
	std::string GetMP();
	std::string GetGold();
	std::string GetKey();
};
