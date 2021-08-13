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
	enum MoveDir {
		UP, 
		DOWN, 
		LEFT, 
		RIGHT
	};
	
	//Stats
	unsigned int
		m_HP,
		m_ATK,
		m_DEF;
	float m_MOVESPEED=10.0f;
	
	CharacterState m_cState=CS_IDLE;
	CharacterState m_lastCState = CS_IDLE;

	Vector2 m_moveDir=Vector2(0.0f,0.0f);
	Vector2 m_lastMoveDir = Vector2(-1.0f, 0.0f);

	bool isWallCollision = false;
	bool isPlayerCollision = false;
	bool isEnemyCollision = false;

	//////////////////////////////////////////////////////////////////////////////////////
	void Update(float frameTime);




	/////////////////////////////////////////////////////////////////////////////////////

	//Funct To Control Move
	void UpdateMoveDirection(Vector2 dir);
	void UpdateMoveDirection(MoveDir dir);
	bool FixedMove(Vector2 dir, float distance, float time, float frameTime);
	void UpdatePosition(float speed, float frameTime);
	void WallCollision(float frameTime);
	void PlayerCollision(float frameTime);
	void EnemyCollision(float frameTime);
	

	Character();
	Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Character();

	
	virtual void Render(Camera *camera);
};