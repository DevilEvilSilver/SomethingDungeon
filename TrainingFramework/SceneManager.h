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

	std::vector<Gold*> m_GoldList;
	std::vector<HPPotion*> m_hpPotionList;
	std::vector<MPPotion*> m_mpPotionList;
	std::vector<SpikeTrap*> m_spikeTrapList;
	std::vector<BombTrap*> m_bombTrapList;

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

	//tien add
	void AddGold(Gold* gold);
	void removeGold(Gold* gold);
	void removeEnemy(Enemy* enemy);
	void AddHPPotion(HPPotion* hpPo);
	void removeHPPotion(HPPotion* hpPo);
	void AddMPPotion(MPPotion* mpPo);
	void removeMPPotion(MPPotion* mpPo);
	void AddSpikeTrap(SpikeTrap* trap);
	void AddBombTrap(BombTrap* trap);
	void removeBombTrap(BombTrap* trap);
};