#pragma once
#include "Object.h"
#include "vector"

struct SkillID {
	std::string prefabID;
	int  iCoolDownTime;
	float fcurrCoolDownTime = 0;
};
class Character : public Object {
protected:
	float m_atk;
	std::vector<SkillID*> m_SkillIDList;
public:
	Character();
	Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Character();
	virtual void Attack(int x, int y);
	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
	float GetAtk();
};