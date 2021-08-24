#pragma once
#include "Object.h"
#include "vector"

struct SkillID {
	std::string prefabID;
	int  iCoolDownTime;
	float fcurrCoolDownTime = 0;
};
class Character : public Object {
protected:
	float m_atk;
	std::vector<SkillID*> m_SkillIDList;
public:

	//STATE
		//enum
		enum CharacterState 
		{
			CS_IDLE,
			CS_MOVE,
			CS_ATTACK,
			CS_GOTHIT,
			CS_DEATH
		};
		//currState
		CharacterState m_cState = CS_IDLE;
	
	//STATS
		int	m_maxHP,
			m_currHP,
			m_ATK,
			m_DEF;


	
	//MOVE
		//speed
		float m_MOVESPEED = 10.0f;
		//dir
		Vector2 m_moveDir=Vector2(0.0f,0.0f);
		Vector2 m_lastMoveDir = Vector2(-1.0f, 0.0f);
		//collision
		bool isWallCollision = false;
		bool isPlayerCollision = false;
		bool isEnemyCollision = false;
		//FixedMove
		float currTime = 0.0f;

	//GOTHIT
		//source causing knockback
		bool m_isInvincible = false;
		bool m_isInvulnerable = false;
		bool m_isKnockBack = false;
		Vector2 m_sourcePos= Vector2(0.0f, 0.0f);
		//dmg
		int m_iDmgTaken = 0;
		int i = 0;

	//ATTACK
		float atkDuration = 1.5f;


	//////////////////////////////////////////////////////////////////////////////////////
	
	//STM :v
	void Update(float frameTime);

	//STATE
	void Idle(float frameTime);
	void Move(float frameTime);
	virtual void Attack(float frameTime);
	virtual bool GotHit(float frameTime);
	virtual void Death(float frameTime);

	//UNIQUE STM :v
	virtual void UniqueUpdate(float frameTime);

	/////////////////////////////////////////////////////////////////////////////////////

	//FUNCT TO MOVE
	void UpdateMoveDirection(Vector2 dir);
	bool FixedMove(Vector2 dir, float distance, float time, float frameTime);
	void UpdatePosition(float speed, float frameTime);
	void WallCollision(float frameTime);
	void PlayerCollision(float frameTime);
	void EnemyCollision(float frameTime);

	//FUNCT GOT HIT
	void UpdateGotHit(int damage, bool isKnockBack, Vector2 pos, float frameTime);
	
	//CHANGE STATE
	void SetCS(CharacterState newState);
	void ResetAnimation();

	//OTHER
	Character();
	Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Character();

	//RENDER
	void Render(Camera *camera);

};