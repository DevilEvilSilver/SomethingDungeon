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
#include "Chest.h"
#include "ArrowTower.h"
#include "Arrow.h"
#include "MiniMap.h"
#include "Gate.h"
#include "Decorations.h"
#include "Effect.h"

#include "define.h"
enum class FloorIdentify {
	FLOOR_1_ID,
	FLOOR_2_ID,
	FLOOR_3_ID,
	FLOOR_BOSS_ID
};
class StatePlay :public StateBase<StatePlay>
{
public:
	
	RoomType m_Map[MAP_HEIGHT][MAP_WIDTH];
	
	//DATA
	std::vector<Object*> m_ObjectList;
	std::vector<Room*> m_RoomList;
	std::vector<Enemy*> m_EnemyList;
	std::vector<Skill*> m_SkillList;
	std::vector<Drop*> m_DropList;
	std::vector<Trap*> m_TrapList;
	
	Player *m_Player;

	std::vector<Decorations*> m_DecorationList;
	std::vector<Effect*> m_EffectList;

	//FOR UPDATE
	std::vector<Room*> m_InRangeRoom;
	std::vector<Enemy*> m_InRangeEnemy;
	std::vector<Skill*> m_InRangeSkill;
	std::vector<Drop*> m_InRangeDrop;
	std::vector<Trap*> m_InRangeTrap;
	std::vector<Effect*> m_InRangeEffect;

	std::vector<Decorations*> m_InRangeDecoration;



	//SOUND
	int m_iHandleBGM;

	//UI
	Button *m_ButtonPause;
	Widget *m_PauseBox;
	Button *m_ButtonResume;
	Button *m_ButtonQuit;
	
	MiniMap* m_MiniMap;

	Widget *m_HpHolder;
	Bar *m_HpBar;
	Text *m_HpText;
	Widget *m_MpHolder;
	Bar *m_MpBar;
	Text *m_MpText;
	Widget *m_MeleeIcon;
	Bar *m_MeleeBar;
	Widget *m_RangeIcon;
	Bar *m_RangeBar;
	Widget* m_DashIcon;
	Bar* m_DashBar;
	Widget *m_GoldIcon;
	Text *m_GoldText;
	Widget *m_KeyIcon;
	Text *m_KeyText;

	Widget *m_GateInstruct;

	Fader *m_TransitionScreen;
	Fader *m_DeathBanner;
	FloorIdentify m_floorID;

	//LOGIC
	bool m_isWinSFX;
	bool m_isGateInstruct;
	bool m_isStartUp;
	bool m_isNextState;
	bool m_isDead;
	bool m_isQuit;
	float m_fNextStateFrame;

	float m_TotalTime;
	unsigned int m_TotalKill;
	unsigned int m_TotalGold;
	unsigned int m_StartUpGold;

	//INIT
	void InitFloorID();
	void Init();
	void MapGenerate(unsigned int maxTunnel, unsigned int maxLength);
	void MapBossGenerate();
	void RoomsGenerate();

	void AddObject(Object* object);
	void AddRoom(Room* room);
	void AddEnemy(Enemy* enemy);
	void AddDecoration(Decorations* decoration);

	void AddDrop(Drop* drop);
	void AddTrap(Trap* trap);
	void AddSkill(Skill* skill);
	void AddEffect(Effect* effect);

	//////////////////////////////////////////////////////////

	void Update(float frameTime);
	
	void UpdateInRange();
	void ClearInRange();
	bool CheckInRange(Vector2 roomID,int delta=1);				//ONLY UPDATE NEAR
	void UpdateRoomID();							//UPDATE ROOM_ID FOR CHARACTER
	void UpdateControl(float frameTime);			//CONTROL PLAYER
	void UpdatePause(float frameTime);				//HANDLE INPUT WHILE PAUSE
	void UpdateResult(float frameTime);				//UPDATE NEXT STATE 
	bool SetRecord(bool isWin);						//SAVE PLAY RECORD

	/////////////////////////////////////////////////////////

	//OTHER
	StatePlay();
	~StatePlay();

	//RENDER
	void GetRenderOrder();
	void Render();

	//tien add

	void Remove();
	void RemoveDrop(Drop* drop);
	void RemoveTrap(Trap* trap);
	void RemoveEnemy(Enemy* enemy);
	void RemoveSkill(Skill* skill);
	void RemoveDecoration(Decorations* deco);
	void RemoveEffect(Effect* effect);
	
};