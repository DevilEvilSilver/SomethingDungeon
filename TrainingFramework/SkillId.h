#pragma once
#include <string>
#include "SkillFeatures.h"
class SkillID {
public:
	std::string m_prefabID;
	SkillCoolDownTime  m_CoolDownTime;
	float m_fCurrCoolDownTime;
	SkillMPCost m_MPCost;
	SkillID(std::string prefabID, SkillCoolDownTime  coolDownTime, SkillMPCost mPCost, float fCurrCoolDownTime = 0);
	~SkillID();
};