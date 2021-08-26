#pragma once
#include "Object.h"
class Decorations:public Object
{
public:
	int hp = 3;


	Decorations(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Decorations();
};

