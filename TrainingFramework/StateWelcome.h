#pragma once
#include <vector>
#include "StateBase.h"
#include "Text.h"
#include "Room.h"

class StateWelcome :public StateBase<StateWelcome>
{
public:
	Object *m_Background;
	Camera *m_Camera;

	StateWelcome();
	~StateWelcome();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};