#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"

class StateShop :public StateBase<StateShop>
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
