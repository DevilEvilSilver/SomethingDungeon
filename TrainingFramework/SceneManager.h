#pragma once
#include <vector>
#include "Object.h"
#include <algorithm> 
#include "Object.h"
#include "define.h"
#include "PhysicEngine.h"
#include "InputManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
class SceneManager {
private:
	static SceneManager* s_Instance;

public:
	std::vector<Object*> m_ObjectList;
	Camera *m_Camera;

	SceneManager();

	void Init();
	void Update(float frameTime);

	//control
	void UpdateControl(float frameTime);
	//game logic

	//collision
	
	void CheckCollision();//logic

	void Render();

	void AddObject(Object *object);
	void GetRenderOrder();

	static SceneManager* GetInstance();
	void ResetInstance();
};