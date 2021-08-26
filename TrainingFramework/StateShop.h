#pragma once
#include "StateBase.h"
#include "Player.h"
#include "Button.h"
#include "Fader.h"
#include "Text.h"

class StateShop :public StateBase<StateShop>
{
public:
	//DATA
	Player *m_Player;

	//UI
	Widget *m_Background;
	Button *m_ButtonStart;

	Button *m_ButtonItem1;
	Button *m_ButtonItem2;
	Button *m_ButtonItem3;

	Text *m_ItemName1;
	Text *m_ItemDescription1;
	Text *m_ItemPrice1;
	Text *m_ItemName2;
	Text *m_ItemDescription2;
	Text *m_ItemPrice2;
	Text *m_ItemName3;
	Text *m_ItemDescription3;
	Text *m_ItemPrice3;

	Text *m_StatHP;
	Text *m_StatMP;
	Text *m_StatATK;
	Text *m_StatDEF;
	Text *m_PlayerGold;

	Fader *m_TransitionScreen;

	//SOUND
	int m_iHandleBGM;

	//LOGIC
	bool m_isStartUp;
	bool m_isPLayState;
	float m_fNextStateFrame;

	StateShop();
	~StateShop();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
}; 
