#pragma once
#include "StateBase.h"
#include "StateManager.h"
#include "Widget.h"
#include "Fader.h"

class StateLoad :public StateBase<StateLoad>
{
public:
	Widget *m_Background;
	Widget *m_LoadingIcon;
	Fader *m_TransitionScreen;

	GameState m_NextState;
	bool m_isNextState;

	StateLoad();
	~StateLoad();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();

	void LoadNewState(GameState newState);
};