#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"

class StateResult :public StateBase<StateResult>
{
public:
	//UI
	Widget *m_Background;
	Widget *m_Title;
	Button *m_ButtonQuit;
	Fader *m_TransitionScreen;

	//SOUND
	int m_iHandleBGM;

	//LOGIC
	bool m_isWin;
	bool m_isStartUp;
	bool m_isWelcomeState;
	float m_fNextStateFrame;

	StateResult();
	~StateResult();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};