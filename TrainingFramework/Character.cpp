#include "stdafx.h"
#include "Character.h"
#include "ResourceManager.h"
#include "Renderer.h"

Character::Character() {}

Character::Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {
	m_atk = 100;
}

Character::~Character()
{

}
void Character::Attack(int x, int y)
{

}
void Character::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Character::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
float Character::GetAtk()
{
	return m_atk;
}