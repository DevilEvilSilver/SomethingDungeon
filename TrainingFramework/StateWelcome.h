#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"

class StateWelcome :public StateBase<StateWelcome>
{
public:
	Widget *m_Background;
	Button *m_ButtonStart;
	Fader *m_TransitionScreen;

	StateWelcome();
	~StateWelcome();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};