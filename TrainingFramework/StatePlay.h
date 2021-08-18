#pragma once
#include <vector>
#include "StateBase.h"
#include "Text.h"
#include "Room.h"
#include "Skill.h"
#include "Player.h"
#include "Enemy.h"
#include"Gold.h"
#include "HPPotion.h"
#include "MPPotion.h"
#include "SpikeTrap.h"
#include "BombTrap.h"


class StatePlay :public StateBase<StatePlay>
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

	std::vector<Drop*> m_DropList;
	std::vector<Trap*> m_TrapList;
	std::vector<Object*> m_DecorationList;


	Player *m_Player;

	//INIT
	void Init();
	void MapGenerate(unsigned int maxTunnel, unsigned int maxLength);
	void RoomsGenerate();
	void AddObject(Object* object);
	void AddRoom(Room* room);
	void AddEnemy(Enemy* enemy);
	void AddDrop(Drop* drop);
	void AddTrap(Trap* trap);
	void AddSkill(Skill* skill);
	void AddDecor(Object* decor);

	//////////////////////////////////////////////////////////

	void Update(float frameTime);
	
	bool CheckInRange(Vector2 roomID);		//ONLY UPDATE NEAR
	void UpdateRoomID();					//UPDATE ROOM_ID FOR CHARACTER
	void UpdateControl(float frameTime);	//CONTROL PLAYER
	
	/////////////////////////////////////////////////////////

	//OTHER
	StatePlay();
	~StatePlay();

	//RENDER
	void GetRenderOrder();
	void Render();

	//tien add


	void RemoveDrop(Drop* drop);
	void RemoveTrap(Trap* trap);

	void RemoveEnemy(Enemy* enemy);
	
};