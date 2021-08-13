#pragma once
#include "Object.h"




class Character : public Object {
public:
	
	enum CharacterState {
		CS_IDLE,
		CS_MOVE,
		CS_ATTACK,
		CS_GOTHIT,
		CS_DASH,
		CS_DEATH
	};
	

	int m_HP, 
		m_ATK,
		m_DEF, 
		m_MOVESPEED=10.0f;
	CharacterState m_cState=CS_IDLE;
	Vector2 m_moveDir=Vector2(0.0f,0.0f);
	Vector2 m_lastMoveDir = Vector2(0.0f, 0.0f);
	
	void UpdateMoveDirection(Vector2 dir);
	void UpdatePosition(float speed, bool isWallCollision, bool isPlayerCollision, bool isEnemyCollision, float frameTime);

	void WallCollision(float frameTime);
	void PlayerCollision(float frameTime);
	void EnemyCollision(float frameTime);

	void IsAttacked(float incomingDamage);

	bool FixedMove(Vector2 dir, float distance, float time,float frameTime);


	Character();
	Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Character();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};