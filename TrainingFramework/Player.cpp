#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "define.h"

#include "define.h"
#include "SceneManager.h"
#include "CollisionManager.h"


Player::Player() {}

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

void Player::Update(float frameTime)
{
	m_fCurrFrameTime += frameTime;


	Go(frameTime,true,false,true);

}

void Player::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}