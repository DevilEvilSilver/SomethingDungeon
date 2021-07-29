#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Animation.h"

class Prefab {
public:
	std::string m_strResourceID;
	unsigned int m_iModelID;
	std::vector<Animation*> m_AnimationList;
	unsigned int m_iShaderID;

	Prefab();
	Prefab(std::string resourceID);
	virtual ~Prefab();
};