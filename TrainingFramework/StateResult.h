#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"
#include "Text.h"

class StateResult :public StateBase<StateResult>
{
public:
	//UI
	Widget *m_Background;
	Widget *m_ResultBox;
	Widget *m_Title;
	Button *m_ButtonQuit;
	Fader *m_TransitionScreen;
	Text *m_TotalTimeText;
	Text *m_TotalKillText;
	Text *m_TotalGoldText;

	//SOUND
	int m_iHandleBGM;

	//LOGIC
	unsigned int m_TotalTime;
	unsigned int m_TotalKill;
	unsigned int m_TotalGold;

	bool m_isWin;
	bool m_isStartUp;
	bool m_isWelcomeState;
	float m_fNextStateFrame;

	StateResult();
	~StateResult();

	void Init();
	std::string GetTime(unsigned int second);

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};