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
	AddSkill(AOE_SKILL);
	AddSkill(BULLET_SKILL);
	AddSkill(DASH);
	m_currentSkillId = AOE_SKILL;
}
Player::~Player() {
	delete numGoldText;
	delete numHPText;
	delete numMPText;
	for (auto& obj : m_UniqueSkillList)
	{
		delete obj;
	}
	m_UniqueSkillList.clear();
}

void Player::UniqueUpdate(float frameTime)
{
	UpdateChangeSkill(frameTime);
}

void Player::Attack(float frameTime)
{

}

//bool Player::Dash(float frameTime)
//{
//	/*if (currDashCD <= 0.0f&&m_cState!=CS_DEATH)
//	{ 
//		SetPS(P_DASH);
//		currDashCD = DashCoolDown;
//		SoundEngine::GetInstance()->Play(WHOOSH, 1.0f, 2.0f, false);
//	}
//	
//	if (m_pState == P_DASH)
//	{
//		m_strState = DASH;
//		if (FixedMove(m_lastMoveDir, m_MOVESPEED, 0.5f, frameTime) == false) return false;
//		SetCS(CS_IDLE);
//		SetPS(P_CS);
//	}*/
//
//	return true;
//}


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
void Player::AddSkill(std::string prefabId)
{
	//AddSkill not play Skill ^^
	SkillID* skillID;
	if (prefabId == AOE_SKILL)
	{
		skillID = new SkillID(AOE_SKILL, SkillCoolDownTime::AOE_CDTIME, SkillMPCost::AOE_MPCOST);
		m_SkillList.push_back(skillID);
	}
	else if (prefabId == BULLET_SKILL)
	{
		skillID = new SkillID(BULLET_SKILL, SkillCoolDownTime::BULLET_CDTIME, SkillMPCost::BULLET_MPCOST);
		m_SkillList.push_back(skillID);

	}
	else if (prefabId == DASH)
	{
		skillID = new SkillID(DASH, SkillCoolDownTime::DASH_CDTIME, SkillMPCost::DASH_MPCOST);
		m_UniqueSkillList.push_back(skillID);
	}
	//more skill here
}
void Player::UpdateChangeSkill(float frameTime) // change current skill
{
	int newKeyPressed = InputManager::GetInstance()->keyPressed;
	static bool bSwitch = true;
	if (newKeyPressed & MOUSE_RIGHT)
	{
		if (bSwitch)
		{
			for (int i = 0; i < m_SkillList.size(); i++)
			{
				if (m_currentSkillId == m_SkillList[i]->m_prefabID)
				{
					if (i == m_SkillList.size() - 1)
					{
						m_currentSkillId = m_SkillList[0]->m_prefabID;
					}
					else
						m_currentSkillId = m_SkillList[i + 1]->m_prefabID;

				}
			}
		}
		bSwitch = false;
	}
	else
	{
		bSwitch = true;
	}

}
void Player::UseSkill(float frameTime)
{
	int keyPressed = InputManager::GetInstance()->keyPressed;
	Vector2 MousePos = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera, InputManager::GetInstance()->mouseLX, InputManager::GetInstance()->mouseLY);
	SkillID* skillID1;
	Skill* NewSkill1;
	Matrix T;
	T.SetIdentity();
	if ((keyPressed & MOUSE_LEFT))
	{
		for (auto& obj : m_SkillList)
		{
			if (m_currentSkillId == obj->m_prefabID)
				skillID1 = obj;
		}
		if ((float)skillID1->m_MPCost < this->m_currMP)
		{
			if ((float)skillID1->m_fCurrCoolDownTime <= 0)
			{
				if (skillID1->m_prefabID == AOE_SKILL)
				{
					NewSkill1 = new AoeSkill(MousePos, this, AOE_SKILL, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill1);
					skillID1->m_fCurrCoolDownTime = (float)skillID1->m_CoolDownTime;
					//Sound
					// Character animation 
					// Character action
				}
				else if (skillID1->m_prefabID == BULLET_SKILL)
				{
					NewSkill1 = new BulletSkill(MousePos, this, BULLET_SKILL, this->m_RoomID, T);
					StatePlay::GetInstance()->AddSkill(NewSkill1);
					skillID1->m_fCurrCoolDownTime = (float)skillID1->m_CoolDownTime;
					//Sound
					// Character animation 
					// Character action
				}
			}
		}
	}
	SkillID* skillID2;
	Skill* NewSkill2;
	if (keyPressed & KEY_SPACE)
	{
		for (auto& obj : m_SkillList)
		{
			if (DASH == obj->m_prefabID)
				skillID2 = obj;
		}
		if ((float)skillID2->m_MPCost < this->m_currMP)
		{
			if ((float)skillID2->m_fCurrCoolDownTime <= 0)
			{
				//Dash Skill Obj
				SoundEngine::GetInstance()->Play(WHOOSH, 1.0f, 2.0f, false);
				//Character Action
				//Character Animation
			}
		}
	}
}
void Player::UpdateCurrentCDTime(float frameTime)
{
	for (auto& obj : m_SkillList)
	{
		obj->m_fCurrCoolDownTime -= frameTime;
	}
	for (auto& obj : m_UniqueSkillList)
	{
		obj->m_fCurrCoolDownTime -= frameTime;
	}
}