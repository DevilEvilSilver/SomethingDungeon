#pragma once
#include "Object.h"

class Character : public Object {
public:


	Character();
	Character(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Character();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};