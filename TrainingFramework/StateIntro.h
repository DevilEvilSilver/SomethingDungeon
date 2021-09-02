#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"

class StateIntro :public StateBase<StateIntro>
{
public:
	//UI
	Widget *m_Background;
	Button *m_ButtonStart;
	Fader *m_TransitionScreen;

	//SOUND
	int m_iHandleBGM;

	//LOGIC
	bool m_isStartUp;
	bool m_isNextState;
	float m_fNextStateFrame;

	StateIntro();
	~StateIntro();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};
#pragma once
