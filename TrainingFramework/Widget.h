#pragma once
#include "Object.h"

class Widget : public Object {
public:
	float m_fCameraPosX, m_fCameraPosY;

	Widget();
	Widget(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Widget();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);

	Matrix GetWorldMatrix(Camera *camera);
};