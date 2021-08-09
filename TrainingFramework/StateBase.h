#pragma once
#include <vector>
#include "Object.h"
#include <memory>

#include "Singleton.h"

template <class T>
class StateBase:public Singleton<T> {

public:
	//data list + camera here
	Camera* m_Camera;

	//deleta all data
	virtual ~StateBase() {};

	//read date from file/ randomize data
	virtual void Init() {};

	//update data + check logic + call updateinput
	virtual void Update(float frameTime) {};

	//input Handler
	virtual void Control(float frameTime) {};

	//render
	virtual void Render() {};

	//to avoid z fighting etc
	virtual void GetRenderOrder() {};
};

	