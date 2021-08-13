#include "stdafx.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"
#include "Skill.h"
#include "AoeSkill.h"
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
	Matrix m;
	m.SetTranslation(x, y, 0.0f);
	float damage = m_atk;
	Skill* Skill1 = new AoeSkill( this,SKILL,this->m_RoomID, m);
	SceneManager::GetInstance()->AddSkill(Skill1);
}
void Player::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	SetPosX(GetPosX() + m_fVx * frameTime);
	SetPosY(GetPosY() + m_fVy * frameTime);
}

void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}