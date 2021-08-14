#include "stdafx.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"
#include "Skill.h"
#include "AoeSkill.h"
#include "InputManager.h"
//#include "AoeSkill.h"
#include "SceneManager.h"
Player::Player() {}

Player::Player(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {
	m_strState = IDLE_LEFT;
}

Player::~Player() {

}
void Player::Attack(int x, int y)
{
	int newKeyPressed = InputManager::GetInstance()->keyPressed;
	Vector2 mousePos = InputManager::GetInstance()->MousePosition(SceneManager::GetInstance()->m_Camera);
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
			SceneManager::GetInstance()->AddSkill(skill);
			bSwitch = false;
			std::cout << "newKeyPressed & MOUSE_LEFT\n";
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
			std::cout << "newKeyPressed & MOUSE_RIGHT\n";
		}
	}
	else
	{
		bSwitch = true;
	}
	
}
void Player::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	SetPosX(GetPosX() + m_fVx * frameTime);
	SetPosY(GetPosY() + m_fVy * frameTime);
}

void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}