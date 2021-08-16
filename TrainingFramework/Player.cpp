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

	m_inumGold = 0;
	std::string goldText = "Gold: " + std::to_string(m_inumGold);
	numGoldText = new Text(goldText, 1, 1, TEXT_COLOR::GREEN, 20, 40, 1.0f);

	m_iCurHP = 100;
	std::string Hptext = "HP: " + std::to_string(m_iCurHP);
	numHPText = new Text(Hptext, 1, 1, TEXT_COLOR::RED, 20, 60, 1.0f);
}
Player::~Player() {
	delete numGoldText;
	delete numHPText;
}

void Player::Attack(int x, int y)
{

	int newKeyPressed = InputManager::GetInstance()->keyPressed;
	Vector2 mousePos = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera,InputManager::GetInstance()->mouseX, InputManager::GetInstance()->mouseY);
	Vector2 playerPos(m_fCurrentPosX, m_fCurrentPosY);
	static int iSwithSkill = 1;
	static bool bSwitch = true;
	Matrix m;
	m.SetTranslation(mousePos.x, mousePos.y,0);
	if ((newKeyPressed & MOUSE_LEFT)  )//
	{
		if (bSwitch && iSwithSkill == 1)
		{
			AoeSkill* skill = new AoeSkill(mousePos,this, AOE_SKILL, this->m_RoomID, m);
			StatePlay::GetInstance()->AddSkill(skill);
			bSwitch = false;

		}
		else if (bSwitch && iSwithSkill == 2)
		{
			BulletSkill* bskill = new BulletSkill(mousePos, this, SKILL, this->m_RoomID, m);
			StatePlay::GetInstance()->AddSkill(bskill);
			bSwitch = false;
			//std::cout << "Player::Attack:\tnewKeyPressed & MOUSE_LEFT:\BulletSkill\n";
		}
	}
	else if ((newKeyPressed & MOUSE_RIGHT))
	{
		if (bSwitch)
		{
			iSwithSkill++;
			if (iSwithSkill == 3)
				iSwithSkill = 1;
			bSwitch = false;
			//std::cout << "newKeyPressed & MOUSE_RIGHT\n";
		}
	}
	else
	{
		bSwitch = true;
	}
	
}

void Player::UpdateCollideGold(float frameTime, Gold* gold) {
	
	increaseGold(gold->getValue());
	numGoldText->setText("Gold: " + std::to_string(m_inumGold));
	StatePlay::GetInstance()->removeGold(gold);
}

void Player::UpdateCollideHP(float frameTime, HPPotion* hp) {
	
	increaseHP(hp->getValue());
	numHPText->setText("HP: " + std::to_string(m_iCurHP));
	StatePlay::GetInstance()->removeHPPotion(hp);
}

// void Player::Render(Camera* camera) {
// 	Renderer::GetInstance()->DrawAnimated(this, camera);

// }


void Player::increaseGold(Gold* gold) {
	m_inumGold += gold->getValue();
}

void Player::increaseGold(int value) {
	m_inumGold += value;
}

void Player::increaseHP(int numHP) {
	m_iCurHP += numHP;
}
