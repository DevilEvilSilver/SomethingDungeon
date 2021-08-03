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

	//Sprite info
	float m_fScaleX, m_fScaleY;
	bool m_isScaleBySize;

	//Hitbox info
	unsigned int m_iType;
	float m_fDeltaX, m_fDeltaY;
	float m_fWidth, m_fHeight;
	float m_fRadius;

	Prefab();
	Prefab(std::string resourceID, unsigned int modelID, unsigned int shaderID, unsigned int type, 
		float deltaX, float deltaY, float width, float height, float radius, float scaleX, float scaleY, unsigned int isScaleBySize);
	virtual ~Prefab();

	void AddAnamation(Animation *animation);
};