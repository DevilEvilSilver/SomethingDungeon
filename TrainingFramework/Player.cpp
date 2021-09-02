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

Player::~Player() {
	delete m_CloseSkillID;
	delete m_RangeSkillID;
	delete m_Dash;
}

void Player::UniqueUpdate(float frameTime)
{
	//m_isInvincible = true;
	switch (m_pState)
	{
		case P_CS:
			break;
		case P_DASH:
			Dash(frameTime);
			break;
		default:
			break;
	}
	//if (m_cState == CS_IDLE || m_cState == CS_MOVE)
	//UseSkill(frameTime);
}

void Player::Attack(float frameTime)
{
}



bool Player::Dash(float frameTime)
{
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
			if (FixedMove(m_lastMoveDir, m_MOVESPEED*0.75f, 0.25f, frameTime) == false) return false;
			m_isInvincible = false;
			SetCS(CS_IDLE);
			m_pState = P_CS;
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
std::string Player::GetHP() {
	return std::to_string(m_currHP) + "/" + std::to_string(m_maxHP);		
}





Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {

	//m_maxHP = 30;
	//m_currHP = 30;
	//m_maxMP = 20;
	//m_currMP = 20;
	//m_ATK = 3;
	//m_DEF = 3;
	//m_GOLD = 1000;

	// read file record
	m_CloseSkillID = NULL;
	m_RangeSkillID = NULL;
	LoadData();
	m_Dash = NULL;
	atkDuration = 0.1f;


	isWallCollision = true;

	m_strState = IDLE_LEFT;
	m_pState = P_CS;


	//AddSkill(SKILL_FIRE2);
	//AddSkill(SKILL_FREEZE2);
	AddSkill(DASH);
	
}

void Player::UseAttack()
{

}

void Player::LoadData() {
	FILE* recordFile;
	recordFile = fopen(FILE_RECORD, "r");

	char strFloor[50];
	unsigned int tmpInt;
	fscanf(recordFile, "%s\n", &strFloor);
	fscanf(recordFile, "Time %d\n", &m_iTmpTime);
	fscanf(recordFile, "Kills %d\n", &m_iTmpKill);
	fscanf(recordFile, "Golds %d\n", &m_iTmpGold);
	fscanf(recordFile, "CurrHP %d\n", &m_currHP);
	fscanf(recordFile, "MaxHP %d\n", &m_maxHP);
	fscanf(recordFile, "CurrMP %d\n", &m_currMP);
	fscanf(recordFile, "MaxMP %d\n", &m_maxMP);
	fscanf(recordFile, "ATK %d\n", &m_ATK);
	fscanf(recordFile, "DEF %d\n", &m_DEF);
	fscanf(recordFile, "Gold %d\n", &m_GOLD);
	fscanf(recordFile, "Key %d\n", &m_KEY);
	fscanf(recordFile, "Speed %f\n", &m_MOVESPEED);
	char strPrefabMelee[50];
	fscanf(recordFile, "Melee %s\n", &strPrefabMelee);
	AddSkill(strPrefabMelee);
	char strPrefabRange[50];
	fscanf(recordFile, "Range %s\n", &strPrefabRange);
	AddSkill(strPrefabRange);
	fclose(recordFile);
}
std::string Player::GetMP() {
	return std::to_string(m_currMP) + "/" + std::to_string(m_maxMP);
}

void Player::AddSkill(std::string prefabId)
{
	// CLOSE SKILL
	SkillID* newSkillID;
	if (prefabId == SKILL_FIRE1)
	{
		if (m_CloseSkillID != NULL)
			delete m_CloseSkillID;
		m_CloseSkillID = new SkillID(SKILL_FIRE1, SkillCoolDownTime::SKILL_FIRE_LV1_CDTIME, SkillMPCost::SKILL_FIRE_LV1_MPCOST);
	}
	else if (prefabId == SKILL_FIRE2)
	{
		if (m_CloseSkillID != NULL)
			delete m_CloseSkillID;
		m_CloseSkillID = new SkillID(SKILL_FIRE2, SkillCoolDownTime::SKILL_FIRE_LV2_CDTIME, SkillMPCost::SKILL_FIRE_LV2_MPCOST);
	}
	else if (prefabId == SKILL_FIRE3)
	{
		if (m_CloseSkillID != NULL)
			delete m_CloseSkillID;
		m_CloseSkillID = new SkillID(SKILL_FIRE3, SkillCoolDownTime::SKILL_FIRE_LV3_CDTIME, SkillMPCost::SKILL_FIRE_LV3_MPCOST);
	}
	//RANGED SKILL
	else if (prefabId == SKILL_FREEZE1)
	{
		if (m_RangeSkillID != NULL)
			delete m_RangeSkillID;
		m_RangeSkillID = new SkillID(SKILL_FREEZE1, SkillCoolDownTime::SKILL_FREEZE_LV1_CDTIME,SkillMPCost::SKILL_FREEZE_LV1_MPCOST);
	}
	else if (prefabId == SKILL_FREEZE2)
	{
		if (m_RangeSkillID != NULL)
			delete m_RangeSkillID;
		m_RangeSkillID = new SkillID(SKILL_FREEZE2, SkillCoolDownTime::SKILL_FREEZE_LV2_CDTIME, SkillMPCost::SKILL_FREEZE_LV2_MPCOST);
	}
	else if (prefabId == SKILL_FREEZE3)
	{
		if (m_RangeSkillID != NULL)
			delete m_RangeSkillID;
		m_RangeSkillID = new SkillID(SKILL_FREEZE3, SkillCoolDownTime::SKILL_FREEZE_LV3_CDTIME, SkillMPCost::SKILL_FREEZE_LV3_MPCOST);
	}
	//DASH
	else if (prefabId == DASH)
	{
		if (m_Dash != NULL)
			delete m_Dash;
		m_Dash = new SkillID(DASH, SkillCoolDownTime::DASH_CDTIME, SkillMPCost::DASH_MPCOST );
	}

}

void Player::UseSkill(float frameTime)
{
	int keyPressed = InputManager::GetInstance()->keyPressed;
	Vector2 MousePos = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera, InputManager::GetInstance()->mouseRX, InputManager::GetInstance()->mouseRY);
	Skill* NewSkill;
	Matrix T;
	T.SetIdentity();

	if ((keyPressed & MOUSE_LEFT))
	{
		if ((float)m_CloseSkillID->m_MPCost <= this->m_currMP)
		{
			if ((float)m_CloseSkillID->m_fCurrCoolDownTime <= 0)
			{
				if (m_CloseSkillID->m_prefabID == SKILL_FIRE3)
				{
					NewSkill = new AoeSkill(this, SKILL_FIRE3, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill);
					m_CloseSkillID->m_fCurrCoolDownTime = (float)m_CloseSkillID->m_CoolDownTime/1000;
					
					//Sound
					//
					// Character action state
				}
				else if (m_CloseSkillID->m_prefabID == SKILL_FIRE2)
				{
					NewSkill = new AoeSkill(this, SKILL_FIRE2, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill);
					m_CloseSkillID->m_fCurrCoolDownTime = (float)m_CloseSkillID->m_CoolDownTime / 1000;
					//Sound
					//
					// Character action state
				}
				else if (m_CloseSkillID->m_prefabID == SKILL_FIRE1)
				{
					NewSkill = new AoeSkill(this, SKILL_FIRE1, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill);
					m_CloseSkillID->m_fCurrCoolDownTime = (float)m_CloseSkillID->m_CoolDownTime / 1000;
					//Sound
					//
					// Character action state
				}
				
			}
		}
	}
	if ((keyPressed & MOUSE_RIGHT))
	{
		if ((float)m_RangeSkillID->m_MPCost <= this->m_currMP)
		{
			if ((float)m_RangeSkillID->m_fCurrCoolDownTime <= 0)
			{
				if (m_RangeSkillID->m_prefabID == SKILL_FREEZE3)
				{
					NewSkill = new BulletSkill(MousePos,this, SKILL_FREEZE3, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill);
					m_RangeSkillID->m_fCurrCoolDownTime = (float)m_RangeSkillID->m_CoolDownTime/1000;
					m_currMP -= (float)m_RangeSkillID->m_MPCost;
					//Sound
					// Character animation 
					// Character action
				}
				else if (m_RangeSkillID->m_prefabID == SKILL_FREEZE2)
				{
					NewSkill = new BulletSkill(MousePos,this, SKILL_FREEZE2, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill);
					m_RangeSkillID->m_fCurrCoolDownTime = (float)m_RangeSkillID->m_CoolDownTime / 1000;
					m_currMP -= (float)m_RangeSkillID->m_MPCost;
					//Sound
					// Character animation 
					// Character action
				}
				else if (m_RangeSkillID->m_prefabID == SKILL_FREEZE1)
				{
					NewSkill = new BulletSkill(MousePos,this, SKILL_FREEZE1, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill);
					m_RangeSkillID->m_fCurrCoolDownTime = (float)m_RangeSkillID->m_CoolDownTime / 1000;
					m_currMP -= (float)m_RangeSkillID->m_MPCost;
					//Sound
					// Character animation 
					// Character action
				}
			}
		}
	}
	if (keyPressed & KEY_SPACE)
	{
		if (m_pState!=P_DASH&&(float)m_Dash->m_MPCost <= this->m_currMP&&(float)m_Dash->m_fCurrCoolDownTime <= 0)
		{
			//Dash Skill Obj
			SoundEngine::GetInstance()->Play(WHOOSH, 1.0f, 2.0f, false);
			m_Dash->m_fCurrCoolDownTime = (float)m_Dash->m_CoolDownTime / 1000;
			//Character Action
			ResetAnimation();
			m_pState = P_DASH;
			i = 0;
			Dash(frameTime);
			//Character Animation
		}
		
	}
}
void Player::UpdateCurrentCDTime(float frameTime)
{
	m_CloseSkillID->m_fCurrCoolDownTime -= frameTime;
	m_RangeSkillID->m_fCurrCoolDownTime -= frameTime;
	m_Dash->m_fCurrCoolDownTime -= frameTime;
}

std::string Player::GetGold() {
	return std::to_string(m_GOLD);
}

std::string Player::GetKey() {
	return std::to_string(m_KEY);
}

std::string Player::GetCloseSkill() {
	return m_CloseSkillID->m_prefabID;
}

std::string Player::GetRangeSkill() {
	return m_RangeSkillID->m_prefabID;
}

std::string Player::GetCloseSkillName() {
	std::string prefabId = m_CloseSkillID->m_prefabID;

	if (prefabId == SKILL_FIRE1)
	{
		return "Flame Sword";
	}
	if (prefabId == SKILL_FIRE2)
	{
		return "Pyro Wave";
	}
	if (prefabId == SKILL_FIRE3)
	{
		return "Solar Descend";
	}

	return "";
}

std::string Player::GetRangeSkillName() {
	std::string prefabId = m_RangeSkillID->m_prefabID;

	if (prefabId == SKILL_FREEZE1)
	{
		return "Ice Arrow";
	}
	if (prefabId == SKILL_FREEZE2)
	{
		return "Glacial Blast";
	}
	if (prefabId == SKILL_FREEZE3)
	{
		return "Absolute Zero";
	}

	return "";
}

float Player::GetCloseSkillMaxCD() {
	return(float)m_CloseSkillID->m_CoolDownTime / 1000;
}
float Player::GetRangeSkillMaxCD() {
	return(float)m_RangeSkillID->m_CoolDownTime / 1000;
}

float Player::GetCloseSkillCurrCD() {
	return(float)m_CloseSkillID->m_fCurrCoolDownTime;
}
float Player::GetRangeSkillCurrCD() {
	return(float)m_RangeSkillID->m_fCurrCoolDownTime;
}
