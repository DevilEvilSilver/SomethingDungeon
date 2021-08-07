#pragma once
#include "StateBase.h"


class StateTest:public StateBase<StateTest>
{
public:
	std::vector<Object*> m_ObjectList;

	StateTest();
	~StateTest();	

	void Init();	
	void Update(float frameTime);	

	void Control(float frameTime);	//test only

	void DraggingObject();			//test only

	void AddObject(Object* object); 

	void CheckCollision();			//test only

	void Render();

	void GetRenderOrder();
};

