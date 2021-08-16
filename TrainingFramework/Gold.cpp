#pragma once
#include"stdafx.h"
#include "Gold.h"
#include "define.h"
#include "ResourceManager.h"
#include "Renderer.h"

Gold::Gold() {}
Gold::~Gold() {}

Gold::Gold(std::string prefabID, Vector2 roomID, Matrix translationMatrix, int value, bool isDisplay)
	: Drop(prefabID, roomID, translationMatrix) {
	m_strState = GOLD_SPIN;
	m_iValue = value;
	//m_isDisplay = isDisplay;
}

void Gold::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void Gold::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

int Gold::getValue() {
	return m_iValue;
}