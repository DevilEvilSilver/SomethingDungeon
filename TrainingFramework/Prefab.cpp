#include <stdafx.h>
#include "Prefab.h"

Prefab::Prefab() {

}

Prefab::Prefab(std::string resourceID)
	: m_strResourceID(resourceID) {
	
}

Prefab::~Prefab() {
	for (auto& object : m_AnimationList) {
		delete object;
	}
	m_AnimationList.resize(0);
}

