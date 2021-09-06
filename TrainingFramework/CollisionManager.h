#pragma once
#include <iostream>
#include "StatePlay.h"
#include "../Utilities/Math.h"
#include "math.h"
#include "cstdlib"
class CollisionManager
{
private:

public:
	CollisionManager();
	~CollisionManager();
	static void UpdateCollision(float frameTime);
	static bool CheckCollision(Object* o1, Object* o2, float frameTime = 0.0f);
	static bool CheckRectRectCollision(Object* dynamicObj, Object* staticObj, float frameTime);
	static bool CheckRectRectCollision2(Object* dynamicObj, Object* staticObj, float frameTime);
};

