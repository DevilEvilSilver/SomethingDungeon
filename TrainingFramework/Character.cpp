#include "stdafx.h"
#include "Character.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

Character::Character() {}

Character::Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

void Character::Update(float frameTime)
{
	if (m_currHP <= 0)
	{
		SetCS(CS_DEATH);
	}

	switch (m_cState)
	{
	case CS_IDLE:
		Idle(frameTime);
		break;
	case CS_MOVE:
		Move(frameTime);
		break;
	case CS_ATTACK:
		Attack(frameTime);
	case CS_GOTHIT:
		GotHit(frameTime);
		break;
	case CS_DEATH:
		
		Death(frameTime);
		break;
	}

	UniqueUpdate(frameTime);

	//ANIMATION
	m_fCurrFrameTime += frameTime;

	//COOLDOWN
}

void Character::Idle(float frameTime)
{
	m_strState = IDLE_LEFT;
}

void Character::Move(float frameTime)
{
	m_strState = MOVE;


	if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
	{
		m_lastMoveDir = m_moveDir;
		UpdatePosition(m_MOVESPEED, frameTime);
	}
	else SetCS(CS_IDLE);
}

void Character::Attack(float frameTime)
{
}

bool Character::GotHit(/*int damage, Vector2 sourcePos,*/float frameTime)
{
	

	Vector2 knockBackDir=Vector2(0.0f,0.0f);

	if (m_cState != CS_GOTHIT&&m_cState!=CS_DEATH)
	{
		m_currHP -= m_iDmgTaken;

		knockBackDir = -(m_sourcePos - GetPos());
		SetCS(CS_GOTHIT);

		

	}
		
	

	if (m_cState == CS_GOTHIT&&m_isKnockBack==true)
	{
		
		m_strState = IDLE_LEFT; //hit animation
		
		
		
		switch (i)
		{
		case 0:
			if (FixedMove(knockBackDir, 5.5f, 0.25f, frameTime)==false) return false;
			else i++;
			break;
		case 1:
			if (FixedMove(Vector2(1.0f, 0.0f), 0.0f, 0.75f, frameTime)==false) return false;
			else i++;
			break;
		case 2:
			i = 0;
			SetCS(CS_IDLE);
			return true;
			break;
		}
		
	}
	return true;
	
}

void Character::Death(float frameTime)
{

}

void Character::UniqueUpdate(float frameTime)
{
}

void Character::UpdateMoveDirection(Vector2 dir)
{
		m_moveDir = dir;
}

bool Character::FixedMove(Vector2 dir, float distance, float time, float frameTime)
{
	
	float speed = distance / time;
	currTime += frameTime;
	currTime += frameTime;

	if (currTime < time)
	{
		UpdateMoveDirection(dir);
		UpdatePosition(speed, frameTime);
		return false;
	}
	else
	{
		currTime = 0.0f;
		return true;
	}

}
void Character::UpdatePosition(float speed, float frameTime)
{
	if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
	{	
		//Get velocity from move direction 
		m_moveDir.Normalize();
		SetVelocityY(speed * m_moveDir.y);
		SetVelocityX(speed * m_moveDir.x);
	
		//check collision
		if (isWallCollision == true) WallCollision(frameTime);
		if (isPlayerCollision == true) PlayerCollision(frameTime);
		if (isEnemyCollision == true) EnemyCollision(frameTime);

		//change position
		SetPosX(GetPosX() + m_fVx * frameTime);
		SetPosY(GetPosY() + m_fVy * frameTime);
		
		//reset speed+direction
		m_moveDir = Vector2(0.0f, 0.0f);
		SetVelocityX(0.0f);
		SetVelocityY(0.0f);

		//update face direction
		if (m_lastMoveDir.x < 0) m_isFacingLeft = true;
		else m_isFacingLeft = false;
	}
}
void Character::WallCollision(float frameTime)
{
	for (auto& obj : StatePlay::GetInstance()->m_RoomList) {
		if (StatePlay::GetInstance()->CheckInRange(obj->m_RoomID) && obj->m_RoomType == WALL)
			CollisionManager::CheckCollision(this, obj, frameTime);
	}
}
void Character::PlayerCollision(float frameTime)
{
	CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player, frameTime);
}
void Character::EnemyCollision(float frameTime)
{
	for (auto& obj : StatePlay::GetInstance()->m_EnemyList) {
		if (StatePlay::GetInstance()->CheckInRange(obj->m_RoomID))
			if (this != obj)
				CollisionManager::CheckCollision(this, obj, frameTime);
	}
}

void Character::UpdateGotHit(int damage, bool isKnockBack, Vector2 pos, float frameTime)
{
	m_iDmgTaken = damage;
	m_isKnockBack = isKnockBack;
	m_sourcePos = pos;
	GotHit(frameTime);
}



Character::~Character() {}


void Character::Attack(int x, int y)
{}

void Character::SetCS(CharacterState newState)
{
	m_cState = newState;
	ResetAnimation();
}
void Character::ResetAnimation()
{
	m_fCurrFrameTime = 0.0f;
	m_iCurrFrameIndex = 0;
}

void Character::Render(Camera* camera)
{
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
