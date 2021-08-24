#include "stdafx.h"
#include "ResourceManager.h"
#include "StatePlay.h"
#include "Renderer.h"
#include "define.h"


#include "StatePlay.h"
#include "CollisionManager.h"

#include "Skill.h"
#include "AoeSkill.h"
#include "InputManager.h"
#include "BulletSkill.h"

#include "SoundEngine.h"
Player::Player() {}
Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {

	m_maxHP = 30000;
	m_currHP = 30;
	m_maxMP = 20;
	m_currMP = 20;
	m_ATK = 3;
	m_DEF = 3;

	m_MOVESPEED = 6.0f;

	isWallCollision = true;
	m_strState = IDLE_LEFT;

	m_GOLD = 0;
	std::string goldText = "Gold: " + std::to_string(m_GOLD);
	numGoldText = new Text(goldText, 1, 1, TEXT_COLOR::YELLOW, 20, 40, 1.0f);

	m_currHP = m_maxHP;
	std::string Hptext = "HP: " + std::to_string(m_currHP);
	numHPText = new Text(Hptext, 1, 1, TEXT_COLOR::RED, 20, 60, 1.0f);

	m_currMP = m_maxMP;
	std::string Mptext = "MP: " + std::to_string(m_currMP);
	numMPText = new Text(Mptext, 1, 1, TEXT_COLOR::BLUE, 20, 80, 1.0f);
}
Player::~Player() {
	delete numGoldText;
	delete numHPText;
	delete numMPText;
}

void Player::UniqueUpdate(float frameTime)
{
	
}

void Player::Attack(float frameTime)
{

}

bool Player::Dash(float frameTime)
{
	/*if (currDashCD <= 0.0f&&m_cState!=CS_DEATH)
	{ 
		SetPS(P_DASH);
		currDashCD = DashCoolDown;
		SoundEngine::GetInstance()->Play(WHOOSH, 1.0f, 2.0f, false);
	}
	
	if (m_pState == P_DASH)
	{
		m_strState = DASH;
		if (FixedMove(m_lastMoveDir, m_MOVESPEED, 0.5f, frameTime) == false) return false;
		SetCS(CS_IDLE);
		SetPS(P_CS);
	}*/

	return true;
}


void Player::PlayerMove(MoveDir dir)
{
	if (m_cState!=CS_MOVE&&m_cState != CS_GOTHIT&&m_cState!=CS_DEATH) SetCS(CS_MOVE);

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
std::string Player::GetHP() {
	return std::to_string(m_currHP) + "/" + std::to_string(m_maxHP);		
}

std::string Player::GetMP() {
	return std::to_string(m_currMP) + "/" + std::to_string(m_maxMP);
}

std::string Player::GetGold() {
	return std::to_string(m_GOLD);
}