#pragma once
#include "StateBase.h"
#include "StateManager.h"
#include "Widget.h"
#include "Fader.h"

class StateLoad :public StateBase<StateLoad>
{
public:
	//UI
	Widget *m_Background;
	Widget *m_LoadIcon;
	Fader *m_TransitionScreen;

	//LOGIC
	GameState m_NextState;
	bool m_isNextState;
	float m_fStartUpFrame;
	float m_fNextStateFrame;

	StateLoad();
	~StateLoad();

	void Init();

	void Update(float frameTime);
	void UpdateControl(float frameTime);
	void LoadState();

	void Render();

	void GetRenderOrder();

	void ResetResource();
};