#pragma once
#include"Object.h"

class Trap :public Object {
private:

public:
	Trap();
	Trap(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Trap();

	virtual void Update(float frameTime);
	virtual void Render(Camera* camera);

};