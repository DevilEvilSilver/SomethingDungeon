#include <stdafx.h>
#include "Prefab.h"

Prefab::Prefab() {

}

Prefab::Prefab(std::string resourceID, unsigned int modelID, unsigned int shaderID, unsigned int type,
	float deltaX, float deltaY, float width, float height, float radius, float scaleX, float scaleY, unsigned int isScaleBySize)
	: m_strResourceID(resourceID), m_iModelID(modelID), m_iShaderID(shaderID), m_iType(type), m_fDeltaX(deltaX), m_fDeltaY(deltaY), 
	m_fWidth(width), m_fHeight(height), m_fRadius(radius), m_fScaleX(scaleX), m_fScaleY(scaleY), m_isScaleBySize(isScaleBySize) {
	
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

