#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"


void Player::UniqueUpdate(float frameTime)
{
	switch (m_pState)
	{
	case P_CS:
		break;
	case P_DASH:
		Dash(frameTime);
		break;
	case P_SKILL:
		Move(frameTime);
		break;
	}

	//COOLDOWN
	if (currDashCD > 0.0f) currDashCD -= frameTime;
	else currDashCD = 0.0f;
}

bool Player::Dash(float frameTime)
{
	if (currDashCD == 0.0f)
	{ 
		SetPS(P_DASH);
		currDashCD = DashCoolDown;
	}
	
	if (m_pState == P_DASH)
	{
		m_strState = DASH;
		if (FixedMove(m_lastMoveDir, m_MOVESPEED, 0.35f, frameTime) == false) return false;
		SetCS(CS_IDLE);
		SetPS(P_CS);
	}

	return true;
}
bool Player::CoolMove(float frameTime)
{
	static int i = 0;
	switch (i)
	{
	case 0:
		if (FixedMove(Vector2(1.0f, 2.0f), 5.0f, 0.2f, frameTime) == false) return false;
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

void Player::PlayerMove(MoveDir dir)
{
	if (m_cState != CS_MOVE) SetCS(CS_MOVE);

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
void Player::SetPS(PlayerState newPS) {
	m_pState = newPS;
	ResetAnimation();
}


Player::Player(){}
Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	isWallCollision = true;
	m_strState = IDLE_LEFT;
}
Player::~Player() {

}

