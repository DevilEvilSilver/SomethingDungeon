#pragma once
#include <vector>
#include "ObjectInstance.h"
#include "Camera.h"
#include "StateManager.h"

class State1 {
private:
	static State1* s_Instance;

public:
	std::vector<ObjectInstance*> m_StateOjectList;
	//Camera m_Camera;

	//char* m_Source = "StM.txt";

	State1();
	~State1();

	void Init();

	void Update(float frameTime);
	void Render();

	void AddObjectInstance(ObjectInstance* objectInstance);

	static State1* GetInstance();
	void ResetInstance();

};

