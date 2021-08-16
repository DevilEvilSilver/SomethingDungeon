#include "stdafx.h"
#include "Widget.h"
#include "ResourceManager.h"
#include "Renderer.h"

Widget::Widget() {}

Widget::Widget(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

Widget::~Widget() {

}

void Widget::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Widget::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

Matrix Widget::GetWorldMatrix(Camera *camera) {
	SetPosX(m_fCurrentPosX + camera->GetPosition().x);
	SetPosY(m_fCurrentPosY + camera->GetPosition().y);
	return m_WorldMatrix;
}