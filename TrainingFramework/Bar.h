#pragma once
#include "Widget.h"

class Bar : public Widget {
private:
	float m_fInitPosX, m_fInitPosY;
public:
	float m_fMaxValue;
	float m_fBarSize;
	bool m_isHorizontal;

	Bar();
	Bar(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue, bool isHorizontal = true);
	~Bar();

	void Update(float frameTime);
	void Render(Camera *camera);

	void Resize(float value);
	virtual Matrix GetWorldMatrix(Camera* camera);
};