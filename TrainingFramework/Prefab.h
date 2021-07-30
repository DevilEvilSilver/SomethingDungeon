#pragma once
#include <vector>
#include "../Utilities/Math.h"
#include "Animation.h"

class Prefab {
public:
	std::string m_strResourceID;
	unsigned int m_iModelID;
	unsigned int m_iShaderID;
	std::vector<Animation*> m_AnimationList;

	Prefab();
	Prefab(std::string resourceID, unsigned int modelID, unsigned int shaderID);
	virtual ~Prefab();

	void AddAnamation(Animation *animation);
};