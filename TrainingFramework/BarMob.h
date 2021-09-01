#pragma once
#include "Object.h"
class BarMob :
    public Object
{
public:
	float m_fMaxValue;
	float m_fBarSize;
	BarMob();
	BarMob(std::string prefabID, Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue,float barSize = 1);
	virtual ~BarMob();
	void Resize(float value);
	virtual void Update(float frameTime);
	virtual void Render(Camera* camera);
	void SetWorldPos(Vector2 pos);
	virtual Matrix GetWorldMatrix(Camera* camera);
};

