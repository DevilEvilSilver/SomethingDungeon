#pragma once
#include "Object.h"

enum RoomType {
	NORMAL,
	WALL,
	START,
	END,
};

class Room : public Object {
public:
	RoomType m_RoomType;

	Room();
	Room(std::string prefabID, Vector2 roomID, Matrix translationMatrix, RoomType roomType);
	~Room();

	void RoomGenerate();
	void Update(float frameTime);
	void Render(Camera *camera);
	void GenObj(std::string prefabId, int num);
};