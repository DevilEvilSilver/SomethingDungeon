#pragma once
#include "Widget.h"

class Fader : public Widget {
public:
	float m_fCurrTime;
	float m_fFadeTime;
	bool m_isFadeIn;

	Fader();
	Fader(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float fadeTime, unsigned int isFadeIn);
	~Fader();

	void Update(float frameTime);
	void Render(Camera *camera);
};