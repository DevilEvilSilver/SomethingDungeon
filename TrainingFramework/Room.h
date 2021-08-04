#pragma once
#include "Object.h"

class Room : public Object {
public:
	

	Room();
	Room(std::string prefabID, Matrix translationMatrix);
	~Room();

	void Update(float frameTime);
	void Render(Camera *camera);
};