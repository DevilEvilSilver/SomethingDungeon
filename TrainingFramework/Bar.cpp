#include "stdafx.h"
#include "Bar.h"
#include "Renderer.h"
#include "InputManager.h"
#include "define.h"

Bar::Bar() {}

Bar::Bar(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue)
	: Widget(prefabID, roomID, translationMatrix), m_fMaxValue(maxValue) {

	m_fBarSize = m_WorldMatrix.m[0][0];
	Resize(currValue);
}

Bar::~Bar() {

}

void Bar::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Bar::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

void Bar::Resize(float value) {
	float ratio = max(min(value / m_fMaxValue, 1.0f), 0.0f);

	m_WorldMatrix.m[0][0] = ratio * m_fBarSize;
}
