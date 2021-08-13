#include "stdafx.h"
#include "Character.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Character::Character() {}

Character::Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

void Character::Update(float frameTime)
{
	switch (m_cState)
	{
	case CS_IDLE:
		break;
	case CS_MOVE:
		if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
		{
			m_lastMoveDir = m_moveDir;
			UpdatePosition(m_MOVESPEED, frameTime);
		}
		else m_cState = CS_IDLE;


		break;
	case CS_GOTHIT:

		//if (CoolMove(frameTime) == true) m_cState = CS_IDLE;

		break;
	case CS_DASH:
		//if (Dash(frameTime) == true) m_cState = CS_IDLE;

		break;
	}
	//ANIMATION
	m_fCurrFrameTime += frameTime;
}


void Character::UpdateMoveDirection(Vector2 dir)
{
		m_moveDir = dir;
}
void Character::UpdateMoveDirection(MoveDir dir)
{
	
	
		if (m_cState == CS_MOVE || m_cState == CS_IDLE)
		{
			m_cState = CS_MOVE;
			switch (dir) {
			case UP:
				m_moveDir.y++;
				break;
			case DOWN:
				m_moveDir.y--;
				break;
			case LEFT:
				m_moveDir.x--;
				break;
			case RIGHT:
				m_moveDir.x++;
				break;
			}
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
	for (auto& obj : SceneManager::GetInstance()->m_RoomList) {
		if (SceneManager::GetInstance()->CheckInRange(obj->m_RoomID) && obj->m_RoomType == WALL)
			CollisionManager::CheckCollision(this, obj, frameTime);
	}
}
void Character::PlayerCollision(float frameTime)
{
	CollisionManager::CheckCollision(this, SceneManager::GetInstance()->m_Player, frameTime);
}
void Character::EnemyCollision(float frameTime)
{
	for (auto& obj : SceneManager::GetInstance()->m_EnemyList) {
		if (SceneManager::GetInstance()->CheckInRange(obj->m_RoomID))
			if (this != obj)
				CollisionManager::CheckCollision(this, obj, frameTime);
	}
}




bool Character::FixedMove(Vector2 dir,float distance , float time, float frameTime)
{
	static float currTime = 0.0f;
	float speed = distance / time;
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

Character::~Character() {

}
void Character::Render(Camera* camera) 
{
	if (m_lastCState != m_cState) {
		m_fCurrFrameTime = 0.0f;
		m_iCurrFrameIndex = 0;

		m_strState = IDLE_LEFT;
		if (m_cState == CS_MOVE) m_strState = MOVE;
		else if (m_cState == CS_DASH) m_strState = DASH;

		m_lastCState = m_cState;
	}

	Renderer::GetInstance()->DrawAnimated(this, camera);
}