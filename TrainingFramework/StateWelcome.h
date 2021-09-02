#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Fader.h"

class StateWelcome :public StateBase<StateWelcome>
{
public:
	//UI
	Widget *m_Background;
	Widget *m_Title;
	Button *m_ButtonContinue;
	Button *m_ButtonStart;
	Button *m_ButtonInstruction;
	Button *m_ButtonCredit;
	Fader *m_TransitionScreen;

	//SOUND
	int m_iHandleBGM;
	
	//LOGIC
	bool m_isStartUp;
	bool m_isContinueable;
	bool m_isLoadData;
	bool m_isPLayState;
	bool m_isInstructionState;
	bool m_isCreditState;
	float m_fNextStateFrame;

	StateWelcome();
	~StateWelcome();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);
	void InitRecord();

	void Render();

	void GetRenderOrder();
};