#pragma once
#include"Object.h"

class Drop :public Object {
private:

public:
	bool isPicked = false;

	Drop();
	Drop(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	virtual ~Drop();

	void Update(float frameTime);
	virtual void OnCollision();
	

};