#pragma once
#include <vector>
#include "StateBase.h"
#include "Button.h"
#include "Bar.h"
#include "Fader.h"
#include "Text.h"
#include "Room.h"
#include "Skill.h"
#include "Player.h"
#include "Enemy.h"
#include "Gold.h"
#include "HPPotion.h"
#include "MPPotion.h"
#include "SpikeTrap.h"
#include "BombTrap.h"


class StatePlay :public StateBase<StatePlay>
{
public:
	
	RoomType m_Map[32][32];
	
	//DATA
	std::vector<Object*> m_ObjectList;
	std::vector<Room*> m_RoomList;
	std::vector<Enemy*> m_EnemyList;
	std::vector<Skill*> m_SkillList;
	std::vector<Drop*> m_DropList;
	std::vector<Trap*> m_TrapList;

	Player *m_Player;
	Object *m_Gate;

	//SOUND
	int m_iHandleBGM;

	//UI
	Button *m_ButtonPause;
	Widget *m_PauseBox;
	Button *m_ButtonResume;
	Button *m_ButtonQuit;

	Widget *m_HpHolder;
	Bar *m_HpBar;
	Text *m_HpText;
	Widget *m_MpHolder;
	Bar *m_MpBar;
	Text *m_MpText;
	Widget *m_GoldIcon;
	Text *m_GoldText;

	Fader *m_TransitionScreen;
	Fader *m_DeathBanner;

	//LOGIC
	bool m_isStartUp;
	bool m_isNextState;
	bool m_isDead;
	bool m_isQuit;
	float m_fNextStateFrame;

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

	//////////////////////////////////////////////////////////

	void Update(float frameTime);
	
	bool CheckInRange(Vector2 roomID);				//ONLY UPDATE NEAR
	void UpdateRoomID();							//UPDATE ROOM_ID FOR CHARACTER
	void UpdateControl(float frameTime);			//CONTROL PLAYER
	void UpdatePause(float frameTime);				//HANDLE INPUT WHILE PAUSE
	void UpdateResult(float frameTime);				//UPDATE NEXT STATE 
	void SetRecord(bool isWin, unsigned int score);	//SAVE PLAY RECORD

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