#include <stdafx.h>
#include "Prefab.h"

Prefab::Prefab() {

}

Prefab::Prefab(std::string resourceID, unsigned int modelID, unsigned int shaderID)
	: m_strResourceID(resourceID), m_iModelID(modelID), m_iShaderID(shaderID) {
	
}

Prefab::~Prefab() {
	for (auto& object : m_AnimationList) {
		delete object;
	}
	m_AnimationList.resize(0);
}

void Prefab::AddAnamation(Animation *animation) {
	m_AnimationList.push_back(animation);
}

