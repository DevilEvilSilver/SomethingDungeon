#pragma once
#include "Widget.h"

class Bar : public Widget {
public:
	float m_fMaxValue;
	float m_fBarSize;

	Bar();
	Bar(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue);
	~Bar();

	void Update(float frameTime);
	void Render(Camera *camera);

	void Resize(float value);
};