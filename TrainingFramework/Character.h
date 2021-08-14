#pragma once
#include "Object.h"




class Character : public Object {
public:
	
	//ENUM
	enum CharacterState 
	{
		CS_IDLE,
		CS_MOVE,
		CS_ATTACK,
		CS_GOTHIT,
		CS_DEATH,
	};
	
	//STATS
	unsigned int
		m_HP,
		m_ATK,
		m_DEF;
	float m_MOVESPEED=10.0f;
	
	//STATE
	CharacterState m_cState=CS_IDLE;
	CharacterState m_lastCState = CS_IDLE;

	//MOVE
	Vector2 m_moveDir=Vector2(0.0f,0.0f);
	Vector2 m_lastMoveDir = Vector2(-1.0f, 0.0f);

	//COLLISION
	bool isWallCollision = false;
	bool isPlayerCollision = false;
	bool isEnemyCollision = false;

	//////////////////////////////////////////////////////////////////////////////////////
	
	//STM :v
	void Update(float frameTime);

	//STATE
	void Idle(float frameTime);
	void Move(float frameTime);
	void Attack(float frameTime);
	void GotHit(float frameTime);
	void Death(float frameTime);

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