#include "stdafx.h"
#include "Button.h"
#include "Renderer.h"
#include "InputManager.h"
#include "define.h"

Button::Button() {}

Button::Button(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Widget(prefabID, roomID, translationMatrix), m_isAvailble(true) {
	m_strState = B_NORMAL;
}

Button::~Button() {

}

void Button::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	if (m_isAvailble) {
		m_strState = B_NORMAL;
	}
	else {
		m_strState = B_UNAVAILABLE;
	}
}

void Button::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}

bool Button::isPressed(Camera* camera) {
	int keyPressed = InputManager::GetInstance()->keyPressed;
	Vector2 mousePos = InputManager::GetInstance()->
		GetMousePosition(camera, InputManager::GetInstance()->mouseLX, InputManager::GetInstance()->mouseLY);

	if ((keyPressed & MOUSE_LEFT) &&
		(mousePos.x >= m_fCurrentPosX) && (mousePos.x <= m_fCurrentPosX + m_fWidth) &&
		(mousePos.y <= m_fCurrentPosY) && (mousePos.y >= m_fCurrentPosY - m_fHeight) &&
		m_isAvailble) {

		m_strState = B_PRESSED;
		return true;
	}
	else {
		if (m_isAvailble) {
			m_strState = B_NORMAL;
		}
		else {
			m_strState = B_UNAVAILABLE;
		}
		return false;
	}
}