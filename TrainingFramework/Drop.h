#pragma once
#include"Object.h"

class Drop :public Object {
private:

public:
	Drop();
	Drop(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Drop();

	virtual void Update(float frameTime);
	virtual void Render(Camera* camera);

};