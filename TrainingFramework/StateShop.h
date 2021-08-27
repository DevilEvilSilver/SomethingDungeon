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

	Button *m_ButtonPause;
	Widget *m_PauseBox;
	Button *m_ButtonResume;
	Button *m_ButtonQuit;

	std::vector<Button*> m_ButtonItemList;
	std::vector<Text*> m_ItemNameList;
	std::vector<Text*> m_ItemDescriptionList;
	std::vector<Text*> m_ItemPriceList;

	Widget *m_ItemGoldIcon;

	Text *m_StatHP;
	Text *m_StatMP;
	Text *m_StatATK;
	Text *m_StatDEF;
	Text *m_PlayerGold;
	Widget *m_PlayerGoldIcon;

	Fader *m_TransitionScreen;

	//SOUND
	int m_iHandleBGM;

	//LOGIC
	bool m_isStartUp;
	bool m_isPLayState;
	bool m_isQuit;
	float m_fNextStateFrame;

	StateShop();
	~StateShop();

	void Init();
	void GenerateItem();

	void AddItemButton(Button* button);
	void AddItemName(Text* name);
	void AddItemDescription(Text* description);
	void AddItemPrice(Text* price);

	void Update(float frameTime);

	void UpdateControl(float frameTime);
	void UpdatePause(float frameTime);
	void UpdateItemLogic(unsigned int itemIndex);
	void SetRecord();

	void Render();

	void GetRenderOrder();
}; 
