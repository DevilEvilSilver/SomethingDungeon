#pragma once
#include"Object.h"

class Trap :public Object {
private:

public:
	bool isExploded = false;
	Trap();
	Trap(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Trap();

	virtual void Update(float frameTime);


};