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

void Player::ShootChicken(Vector2 target)
{
	if (currChickenCD <= 0.0f&&m_currMP>=ChickenMPCost) {
		
		currChickenCD = ChickenCoolDown;

		Matrix m;
		m.SetTranslation(target.x, target.y, 0);

		BulletSkill* bskill = new BulletSkill(target, this, SKILL_2, this->m_RoomID, m);
		StatePlay::GetInstance()->AddSkill(bskill);

		m_currMP -= ChickenMPCost;
		numMPText->setText("MP: " + std::to_string(m_currMP));

		SoundEngine::GetInstance()->Play(PEWPEW, 1.0f, 1.0f, false);
	}

	
}

void Player::Melee(Vector2 target)
{
	if (currMeleeCD <= 0.0f) {
		SetCS(CS_ATTACK);
		currMeleeCD = MeleeCoolDown;
	
		Matrix m;
		m.SetTranslation(target.x, target.y, 0);

		AoeSkill* bskill = new AoeSkill(target, this, AOE_SKILL, this->m_RoomID, m);
		StatePlay::GetInstance()->AddSkill(bskill);
	}
}


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
		break;
	}

	//COOLDOWN
	if (currDashCD > 0.0f) currDashCD -= frameTime;
	if (currChickenCD>0.0f)currChickenCD -= frameTime;
	if (currMeleeCD > 0.0f) currMeleeCD -= frameTime;
}



bool Player::Dash(float frameTime)
{
	if (currDashCD <= 0.0f&&m_cState!=CS_DEATH)
	{ 
		SetCS(CS_IDLE);
		SetPS(P_DASH);
		currTime = 0.0f;
		currDashCD = DashCoolDown;
		SoundEngine::GetInstance()->Play(WHOOSH, 1.0f, 2.0f, false);
		i = 0;
	}
	
	if (m_pState == P_DASH)
	{
		
		m_strState = DASH;

		switch (i)
		{
		case 0:
			if (FixedMove(m_lastMoveDir, 0.0f, 0.1f, frameTime) == false) return false;
			m_isInvincible = true;
			i++;
			break;
		case 1:
			if (FixedMove(m_lastMoveDir, m_MOVESPEED*1.5f, 0.5f, frameTime) == false) return false;
			m_isInvincible = false;
			SetCS(CS_IDLE);
			SetPS(P_CS);
			break;
		}

	}

	return true;
}


void Player::PlayerMove(MoveDir dir)
{
	if (m_cState!=CS_MOVE&&m_cState != CS_GOTHIT&&m_cState!=CS_DEATH&&m_cState!=CS_ATTACK) SetCS(CS_MOVE);

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

	m_maxHP = 30;
	m_currHP = 30;
	m_maxMP = 20;
	m_currMP = 20;
	m_ATK = 3;
	m_DEF = 3;

	atkDuration = 0.25f;

	m_MOVESPEED = 3.0f;

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

void Player::UseAttack()
{
	if (m_cState != CS_GOTHIT && m_cState != CS_DEATH)
	{
		int newKeyPressed = InputManager::GetInstance()->keyPressed;
		Vector2 mousePos = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera, InputManager::GetInstance()->mouseX, InputManager::GetInstance()->mouseY);
		Vector2 playerPos(m_fCurrentPosX, m_fCurrentPosY);

		if ((newKeyPressed & MOUSE_LEFT))
		{
			Melee(mousePos);
		}
		if ((newKeyPressed & MOUSE_RIGHT))
		{
			ShootChicken(mousePos);
		}
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