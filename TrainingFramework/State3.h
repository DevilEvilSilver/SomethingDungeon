#pragma once
#include <vector>
#include "ObjectInstance.h"
#include "Camera.h"

class State3 {
private:
	static State3* s_Instance;

public:
	std::vector<ObjectInstance*> m_StateOjectList;
	//Camera m_Camera;

	//char* m_Source = "StM.txt";

	State3();
	~State3();

	void Init();

	void Update(float frameTime);
	void Render();

	void AddObjectInstance(ObjectInstance* objectInstance);

	static State3* GetInstance();
	void ResetInstance();

};

