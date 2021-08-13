#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"



void Player::PlayerMoveDirection(MoveDir dir)
{
	if (m_cState != CS_GOTHIT)
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

bool Player::CoolMove(float frameTime)
{
	static int i = 0;
	switch(i)
	{
	case 0:
		if (FixedMove(Vector2(1.0f,2.0f),5.0f,0.2f,frameTime)==false) return false;
		else i++;
		break;
	case 1:
		if (FixedMove(Vector2(1.0f, -2.0f), 5.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 2:
		if (FixedMove(Vector2(-2.0f, 1.0f), 5.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 3:
		if (FixedMove(Vector2(5.0f, 0.0f), 5.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 4:
		if (FixedMove(Vector2(-2.0f, -1.0f), 5.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 5:
		if (FixedMove(Vector2(5.0f, 0.0f), 10.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 6:
		if (FixedMove(Vector2(-5.0f, 0.0f), 10.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 7:
		if (FixedMove(Vector2(5.0f, 0.0f), 10.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 8:
		if (FixedMove(Vector2(-5.0f, 0.0f), 10.0f, 0.2f, frameTime) == false) return false;
		else i++;
		break;
	case 9:
		if (FixedMove(Vector2(5.0f, 0.0f), 10.0f, 0.1f, frameTime) == false) return false;
		else i++;
		break;
	case 10:
		if (FixedMove(Vector2(-5.0f, 0.0f), 10.0f, 0.1f, frameTime) == false) return false;
		else i++;
		break;
	case 11:
		if (FixedMove(Vector2(5.0f, 0.0f), 10.0f, 0.1f, frameTime) == false) return false;
		else i++;
		break;
	case 12:
		if (FixedMove(Vector2(-5.0f, 0.0f), 10.0f, 0.1f, frameTime) == false) return false;
		else i++;
		break;
	case 13:
		if (FixedMove(Vector2(5.0f, 0.0f), 10.0f, 0.1f, frameTime) == false) return false;
		else i++;
		break;
	case 14:
		if (FixedMove(Vector2(-5.0f, 0.0f), 10.0f, 0.1f, frameTime) == false) return false;
		else i++;
		break;
	case 15: 
		i = 0;
		return true;
	}

	return false;
}

bool Player::Dash(float frameTime)
{
	printf("dash\n");
	if (FixedMove(m_lastMoveDir, m_MOVESPEED/2.0f, 0.35f, frameTime) == false) return false;
	return true;
}

Player::Player(){}

Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;
}

Player::~Player() {

}

//void Player::Update(float frameTime) {
//	m_fCurrFrameTime += frameTime;
//	SetPosX(GetPosX() + m_fVx * frameTime);
//	SetPosY(GetPosY() + m_fVy * frameTime);
//}



void Player::Update(float frameTime)//call func and animation
{


	switch (m_cState)
	{
	case CS_IDLE:
		
		break;
	case CS_MOVE:
		
		if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
		{
			m_lastMoveDir = m_moveDir;
			UpdatePosition(m_MOVESPEED, true, false, true, frameTime);
		}else m_cState = CS_IDLE;

		
		break;
	case CS_GOTHIT:
		
		if (CoolMove(frameTime)==true) m_cState = CS_IDLE;

		break;
	case CS_DASH:

		if (Dash(frameTime) == true) m_cState = CS_IDLE;

		break;
	}
	
	m_fCurrFrameTime += frameTime;

}



void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}