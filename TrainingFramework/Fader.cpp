#include "stdafx.h"
#include "Fader.h"
#include "Renderer.h"
#include "InputManager.h"
#include "define.h"

Fader::Fader() {}

Fader::Fader(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float fadeTime, unsigned int isFadeIn)
	: Widget(prefabID, roomID, translationMatrix), m_fCurrTime(0.0f), m_fFadeTime(fadeTime), m_isFadeIn(isFadeIn) {

}

Fader::~Fader() {

}

void Fader::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
	if (m_fCurrTime < m_fFadeTime)
		m_fCurrTime += frameTime;
}

void Fader::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
