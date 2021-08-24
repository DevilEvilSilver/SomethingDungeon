#include "stdafx.h"
#include "SkillId.h"
SkillID::SkillID(std::string prefabID, SkillCoolDownTime  coolDownTime, SkillMPCost mPCost, float fCurrCoolDownTime)
{
	m_prefabID = prefabID;
	m_CoolDownTime = coolDownTime;
	m_MPCost = mPCost;
	m_fCurrCoolDownTime = fCurrCoolDownTime;
}
SkillID::~SkillID()
{
}