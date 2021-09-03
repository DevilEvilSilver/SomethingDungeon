#include "stdafx.h"
#include "Widget.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "StatePlay.h"

Widget::Widget() {}

Widget::Widget(std::string prefabID, Vector2 roomID, Matrix translationMatrix, std::string state)
	: Object(prefabID, roomID, translationMatrix) {

	if (strcmp(state.c_str(), ""))
		m_strState = state;

	m_fCameraPosX = translationMatrix.m[3][0];
	m_fCameraPosY = translationMatrix.m[3][1];
}

Widget::~Widget() {

}

void Widget::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Widget::Render(Camera* camera, Vector2 playerPos) {
	Renderer::GetInstance()->DrawAnimated(this, camera,playerPos);
}

Matrix Widget::GetWorldMatrix(Camera *camera) {
	SetPosX(m_fCameraPosX + camera->GetPosition().x);
	SetPosY(m_fCameraPosY + camera->GetPosition().y);
	return m_WorldMatrix;
}