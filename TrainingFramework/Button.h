#pragma once
#include "Widget.h"

class Button : public Widget {
public:
	bool m_isAvailble;

	Button();
	Button(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Button();

	void Update(float frameTime);
	void Render(Camera *camera);

	bool isPressed(Camera* camera);
	bool isHover(Camera* camera);
};