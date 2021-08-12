#pragma once
#include "Object.h"




class Character : public Object {
public:
	
	enum CharacterState {
		CS_IDLE,
		CS_MOVE,
		CS_ATTACK,
		CS_GOTHIT,
		CS_DEATH
	};
	enum MoveDir {
		UP, DOWN, LEFT, RIGHT
	};

	int m_HP, 
		m_ATK,
		m_DEF, 
		m_MOVESPEED=10.0f;
	CharacterState m_cState;
	float m_gotHitTime;	
	Vector2 m_moveDir=Vector2(0.0f,0.0f);
	
	void UpdateMoveDirection(MoveDir dir);
	void Go(float frameTime, bool isWallCollision, bool isPlayerCollision, bool isEnemyCollision);
	void WallCollision(float frameTime);
	void PlayerCollision(float frameTime);
	void EnemyCollision(float frameTime);

	void IsAttacked(float incomingDamage);

	Character();
	Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Character();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};