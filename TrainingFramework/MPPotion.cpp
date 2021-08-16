#include"stdafx.h"
#include "MPPotion.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

MPPotion::MPPotion() {}
MPPotion::~MPPotion()
{
}

MPPotion::MPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = MP_POTION;
	m_iValue = value;
}

void MPPotion::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void MPPotion::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

int MPPotion::getValue() {
	return m_iValue;
}