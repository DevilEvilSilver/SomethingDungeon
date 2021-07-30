#pragma once
#include <vector>
#include "ObjectInstance.h"
#include "Camera.h"

class State2 {
private:
	static State2* s_Instance;

public:
	std::vector<ObjectInstance*> m_StateOjectList;
	Camera m_Camera;

	char* m_Source = "StM.txt";

	State2();
	~State2();

	void Init();

	void Update(float frameTime);
	void Render();

	void AddObjectInstance(ObjectInstance* objectInstance);

	static State2* GetInstance();
	void ResetInstance();

};



