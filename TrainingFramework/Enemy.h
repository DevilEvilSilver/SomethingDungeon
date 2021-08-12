#pragma once
#include "Character.h"

class Enemy : public Character {
public:

	DWORD m_AIrefresh = 200.0l;
	DWORD m_AIstart = 0.0f;
	

	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();

	void UsingAI();

	
	void Update(float frameTime);
	void Render(Camera *camera);
};