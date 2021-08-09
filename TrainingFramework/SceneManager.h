#pragma once
#include <vector>
#include "Object.h"
#include"Text.h"

class SceneManager {
private:
	static SceneManager* s_Instance;
	Text *scoreText ;
	//Text levelText;


public:
	std::vector<Object*> m_ObjectList;
	Camera *m_Camera;

	SceneManager();

	void Init();
	void Update(float frameTime);

	//control
	void Control(float frameTime);
	//game logic

	//collision
	
	void CheckCollision();//logic

	void Render();

	void AddObject(Object *object);
	void GetRenderOrder();

	static SceneManager* GetInstance();
	void ResetInstance();
};