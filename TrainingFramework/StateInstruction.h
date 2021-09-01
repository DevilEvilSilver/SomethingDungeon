#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"

class StateInstruction :public StateBase<StateInstruction>
{
public:
	//UI
	Widget *m_Background;
	Button *m_ButtonQuit;
	Fader *m_TransitionScreen;

	//SOUND
	int m_iHandleBGM;

	//LOGIC
	bool m_isStartUp;
	bool m_isWelcomeState;
	float m_fNextStateFrame;

	StateInstruction();
	~StateInstruction();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};