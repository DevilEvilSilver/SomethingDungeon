#pragma once
#include <vector>
#include "ObjectInstance.h"
#include "Camera.h"

class StateBase {
private:
	static StateBase* s_Instance;

public:
	std::vector<ObjectInstance*> m_StateOjectList;
	Camera* m_Camera;

	char* m_Source = new char[30];

	StateBase();
	~StateBase();

	void Init();

	void Update(float frameTime);
	void Render();

	void AddObjectInstance(ObjectInstance* objectInstance);

	static StateBase* GetInstance();
	static void ResetInstance();
};
