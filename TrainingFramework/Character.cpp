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

}

void Character::UpdateMoveDirection(MoveDir dir)
{
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

void Character::Go(float frameTime, bool isWallCollision, bool isPlayerCollision, bool isEnemyCollision)
{
	if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
	{
		//Get velocity from move direction 
		m_moveDir.Normalize();
		SetVelocityY(m_MOVESPEED * m_moveDir.y);
		SetVelocityX(m_MOVESPEED * m_moveDir.x);

		//check collision
		if (isWallCollision == true) WallCollision(frameTime);
		if (isPlayerCollision == true) PlayerCollision(frameTime);
		if (isEnemyCollision == true) EnemyCollision(frameTime);

		//change position
		if (m_cState != CS_GOTHIT) {
			SetPosX(GetPosX() + m_fVx * frameTime);
			SetPosY(GetPosY() + m_fVy * frameTime);
			m_cState = CS_MOVE;
		}

		//reset speed+direction
		m_moveDir = Vector2(0.0f, 0.0f);
		SetVelocityX(0.0f);
		SetVelocityY(0.0f);
	}
}

void Character::IsAttacked(float incomingDamage)
{
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


Character::~Character() {

}



void Character::Render(Camera* camera) {

	switch (m_cState) {
	case CS_IDLE:/*m_strState=.....*/break;
	case CS_ATTACK:break;
	case CS_GOTHIT:break;
	case CS_MOVE:break;
	case CS_DEATH:break;
	}
	m_strState = IDLE_LEFT;

	//reset char state
	m_cState = CS_IDLE;

	Renderer::GetInstance()->DrawAnimated(this, camera);
}