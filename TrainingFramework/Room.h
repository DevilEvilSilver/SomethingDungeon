#pragma once
#include "Object.h"

enum RoomType {
	NORMAL,
	WALL,
	START,
	END,
	KEY_ROOM
};

class Room : public Object {
public:
	RoomType m_RoomType;
	bool m_isRenderLast = false;


	Room();
	Room(std::string prefabID, Vector2 roomID, Matrix translationMatrix, RoomType roomType);
	~Room();

	void RoomGenerate();
	void Floor1Generate();
	void Floor2Generate();
	void Floor3Generate();
	void FloorBossGenerate();
	void GenerateDeco();
	void AddDeco(std::string prefabName);
	void AddEnemy(std::string prefabName);
	void Update(float frameTime);
	void Render(Camera *camera);
	void GenObj(std::string prefabId, int num);
};