#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"





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
	if (currDashCD == 0.0f)
	{ 
		m_cState = CS_DASH;
		currDashCD = DashCoolDown;
	}

	if (m_cState == CS_DASH) 
	{
		if (FixedMove(m_lastMoveDir, m_MOVESPEED, 0.35f, frameTime) == false) return false;
	}
	return true;
}

Player::Player(){
	
}

Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	isWallCollision = true;
	m_strState = IDLE_LEFT;
}

Player::~Player() {

}

void Player::UpdatePlayer(float frameTime)//call func and animation
{

	//LOGIC STATE
	//{
	//	switch (m_cState)
	//	{
	//	case CS_IDLE:
	//		break;
	//	case CS_MOVE:
	//		if (!(m_moveDir.x == 0.0f && m_moveDir.y == 0.0f))
	//		{
	//			m_lastMoveDir = m_moveDir;
	//			UpdatePosition(m_MOVESPEED, frameTime);
	//		}
	//		else m_cState = CS_IDLE;


	//		break;
	//	case CS_GOTHIT:

	//		if (CoolMove(frameTime) == true) m_cState = CS_IDLE;

	//		break;
	//	case CS_DASH:
	//		if (Dash(frameTime) == true) m_cState = CS_IDLE;

	//		break;
	//	}

	//}

	////COOLDOWN
	//if (currDashCD > 0.0f) currDashCD -= frameTime;
	//else currDashCD = 0.0f;
	//
	////ANIMATION
	//m_fCurrFrameTime += frameTime;
	Update(frameTime);
}



void Player::Render(Camera* camera) {
	
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