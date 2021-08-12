#pragma once
#include <vector>
#include "StateBase.h"
#include "Button.h"
#include "Room.h"

class StateWelcome :public StateBase<StateWelcome>
{
public:
	Widget *m_Background;
	Button *m_ButtonStart;

	StateWelcome();
	~StateWelcome();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};