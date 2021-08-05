#pragma once
#include <vector>
#include "Room.h"
#include "Player.h"
#include "Enemy.h"

class SceneManager {
private:
	static SceneManager* s_Instance;

public:
	RoomType m_Map[32][32];
	std::vector<Room*> m_RoomList;
	std::vector<Enemy*> m_EnemyList;
	std::vector<Object*> m_ObjectList;
	Player *m_Player;
	Camera *m_Camera;

	SceneManager();

	void Init();
	void MapGenerate(unsigned int maxTunnel, unsigned int maxLength);
	void Update(float frameTime);

	//control
	void Control(float frameTime);
	//game logic

	//collision
	
	void CheckCollision();//logic

	void Render();

	void AddObject(Object *object);
	void AddRoom(Room *room);
	void AddEnemy(Enemy *enemy);
	void GetRenderOrder();

	static SceneManager* GetInstance();
	void ResetInstance();
};