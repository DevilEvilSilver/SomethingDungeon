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

void Character::UpdateMoveDirection(Vector2 dir)
{
		m_moveDir = dir;
}

void Character::UpdatePosition(float speed, bool isWallCollision, bool isPlayerCollision, bool isEnemyCollision, float frameTime)
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

void Character::IsAttacked(float incomingDamage)
{	
	m_cState = CS_GOTHIT;
}



bool Character::FixedMove(Vector2 dir,float distance , float time, float frameTime)
{

	static float currTime = 0.0f;
	float speed = distance / time;
	currTime += frameTime;

	if (currTime < time)
	{
		UpdateMoveDirection(dir);

		UpdatePosition(speed, true, false, true, frameTime);
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
void Character::Render(Camera* camera) {

	
	m_strState = IDLE_LEFT;

	

	Renderer::GetInstance()->DrawAnimated(this, camera);
}