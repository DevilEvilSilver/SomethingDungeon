#include "stdafx.h"
#include "Character.h"
#include "ResourceManager.h"
#include "Renderer.h"

Character::Character() {}

Character::Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

Character::~Character() {

}

void Character::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Character::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}