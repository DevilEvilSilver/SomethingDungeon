#pragma once
#include "StateBase.h"
#include "Widget.h"
#include "Fader.h"

class StateLogo :public StateBase<StateLogo>
{
public:
	Widget *m_Background;
	Fader *m_Logo;
	Fader *m_TransitionScreen;

	StateLogo();
	~StateLogo();

	void Init();

	void Update(float frameTime);

	void UpdateControl(float frameTime);

	void Render();

	void GetRenderOrder();
};