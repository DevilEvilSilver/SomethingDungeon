#pragma once
#include <vector>
#include "StateBase.h"
#include "Text.h"
#include "Room.h"
#include "Skill.h"
#include "Player.h"
#include "Enemy.h"


class SceneManager :public StateBase<SceneManager>
{
private:
	Text *scoreText ;
public:
	
	RoomType m_Map[32][32];
	
	//DATA
	std::vector<Object*> m_ObjectList;
	std::vector<Room*> m_RoomList;
	std::vector<Enemy*> m_EnemyList;

	std::vector<Skill*> m_SkillList;

	Player *m_Player;
	Camera *m_Camera;

	//INIT
	void Init();
	void MapGenerate(unsigned int maxTunnel, unsigned int maxLength);
	void RoomsGenerate();
	void AddObject(Object* object);
	void AddRoom(Room* room);
	void AddEnemy(Enemy* enemy);

	void AddSkill(Skill* skill);

	//////////////////////////////////////////////////////////

	void Update(float frameTime);
	
	bool CheckInRange(Vector2 roomID);		//ONLY UPDATE NEAR
	void UpdateRoomID();					//UPDATE ROOM_ID FOR CHARACTER
	void UpdateControl(float frameTime);	//CONTROL PLAYER
	
	/////////////////////////////////////////////////////////

	//OTHER
	SceneManager();
	~SceneManager();

	//RENDER
	void GetRenderOrder();
	void Render();
};