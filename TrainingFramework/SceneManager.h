#pragma once
#include <vector>
#include "StateBase.h"
#include "Room.h"
#include "Player.h"
#include "Enemy.h"

class SceneManager :public StateBase<SceneManager>
{
public:
	RoomType m_Map[32][32];
	std::vector<Room*> m_RoomList;
	std::vector<Enemy*> m_EnemyList;
	std::vector<Object*> m_ObjectList;
	Player *m_Player;
	Camera *m_Camera;

	SceneManager();
	~SceneManager();

	void Init();
	void MapGenerate(unsigned int maxTunnel, unsigned int maxLength);
	void RoomsGenerate();

	void Update(float frameTime);
	void UpdateRoomID();
	//control
	void Control(float frameTime);
	//game logic

	//collision
	
	void CheckCollision();//logic
	bool CheckInRange(Vector2 roomID);

	void Render();

	void AddObject(Object *object);
	void AddRoom(Room *room);
	void AddEnemy(Enemy *enemy);
	void GetRenderOrder();
};