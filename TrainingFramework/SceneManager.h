#pragma once
#include <vector>
#include "Object.h"
#include "PhysicEngine.h"
class SceneManager {
private:
	static SceneManager* s_Instance;
	Object *m_charactor;
public:
	char m_pKeySignal;
	std::vector<Object*> m_ObjectList;
	Camera *m_Camera;

	SceneManager();
	~SceneManager();

	void Init();
	void Update(float frameTime);
	void Render();

	void AddObject(Object *object);
	void GetRenderOrder();

	static SceneManager* GetInstance();
	static void ResetInstance();
};