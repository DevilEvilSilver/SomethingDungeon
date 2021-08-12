#pragma once
#include "StateBase.h"
#include "Button.h"
#include "Room.h"

class StateLogo :public StateBase<StateLogo>
{
public:
	Widget *m_Background;
	Widget *m_Logo;

	StateLogo();
	~StateLogo();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};