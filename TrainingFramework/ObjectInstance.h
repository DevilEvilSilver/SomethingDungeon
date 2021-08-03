#pragma once
#include "stdafx.h"
#include "define.h"
#include "Math.h"
#include "../Utilities/Math.h"
class ObjectInstance
{
public: 
	int ObjectID;
	Vector2 pos;

	ObjectInstance(int id, Vector2 pos);
};

