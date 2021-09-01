#pragma once
#include "BarMob.h"
#include "Camera.h"
#include <string.h>
#include "../Utilities/Math.h"
class EnemyHpMob
{
private:
	BarMob *m_Bound;
	BarMob *m_HpMob;
public:
	EnemyHpMob(Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue, float barSize = 1);
	~EnemyHpMob();
	void Update(float framTime);
	void Render(Camera* camera);
	void Resize(float value);
	void SetWorldPos(Vector2 pos);
};

