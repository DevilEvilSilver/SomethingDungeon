#include "stdafx.h"
#include "Bar.h"
#include "Renderer.h"
#include "InputManager.h"
#include "define.h"

Bar::Bar() {}

Bar::Bar(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue, bool isHorizontal)
	: Widget(prefabID, roomID, translationMatrix), m_fMaxValue(maxValue), m_isHorizontal(isHorizontal) {

	m_fInitPosX = m_WorldMatrix.m[3][0];
	m_fInitPosY = m_WorldMatrix.m[3][1];
	if (m_isHorizontal)
		m_fBarSize = m_WorldMatrix.m[0][0];
	else
		m_fBarSize = m_WorldMatrix.m[1][1];
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

	if (m_isHorizontal)
		m_WorldMatrix.m[0][0] = ratio * m_fBarSize;
	else {
		m_WorldMatrix.m[1][1] = ratio * m_fBarSize;
		m_fCameraPosY = m_fInitPosY - (1- ratio) * m_fBarSize;
	}
}

Matrix Bar::GetWorldMatrix(Camera* camera) {
	SetPosX(m_fCameraPosX + camera->GetPosition().x);
	SetPosY(m_fCameraPosY + camera->GetPosition().y);
	return m_WorldMatrix;
}
