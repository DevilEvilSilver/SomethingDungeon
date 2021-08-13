#pragma once
#include"stdafx.h"
#include "HPPotion.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

HPPotion::HPPotion() {}
HPPotion::~HPPotion() 
{
}

HPPotion::HPPotion(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value, bool isDisplay)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = HP_POTION;
	m_iValue = value;
	//m_isDisplay = isDisplay;
}

void HPPotion::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void HPPotion::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

int HPPotion::getValue() {
	return m_iValue;
}