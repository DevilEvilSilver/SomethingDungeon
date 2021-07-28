#pragma once
#include <vector>
#include "Object.h"

class SceneManager {
private:
	static SceneManager* s_Instance;

public:
	std::vector<Object*> m_ObjectList;
	Camera *m_Camera;

	SceneManager();
	~SceneManager();

	void Init();
	void Update(float frameTime);
	void Render();

	void AddObject(Object *object);

	static SceneManager* GetInstance();
	static void ResetInstance();
};