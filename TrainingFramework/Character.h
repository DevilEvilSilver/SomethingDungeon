#pragma once
#include "Object.h"

class Character : public Object {
public:


	Character();
	Character(std::string prefabID, Matrix translationMatrix);
	~Character();

	virtual void Update(float frameTime);
	virtual void Render(Camera *camera);
};