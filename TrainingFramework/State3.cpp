#include "stdafx.h"
#include "State3.h"
#include "StateManager.h"

#include "ObjectInstance.h"
#include "InputManager.h"
//#include "SceneManager.h"

#include "Camera.h"

State3* State3::s_Instance = NULL;

State3::State3()
{
	Init();
	//SceneManager::GetInstance();
}

State3::~State3()
{
}


void State3::Init()
{
	/*
	FILE* dataFile;
	dataFile = fopen(m_Source, "r");

	int iObjectInstanceCount;
	fscanf(dataFile, "ObjectInstanceNum %d\n", &iObjectInstanceCount);

	while (iObjectInstanceCount--) {
		unsigned int id;
		fscanf(dataFile, "#ID %d\n", &id);

		unsigned int iObjectID;
		fscanf(dataFile, "ObjectID	%d\n", &iObjectID);

		Vector2 pos;
		fscanf(dataFile, "pos %f %f\n", &pos.x, &pos.y);


		ObjectInstance* object = new ObjectInstance(iObjectID, pos);
		AddObjectInstance(object);
	}

	//future feature: Get camera from input
	m_Camera = Camera();

	fclose(dataFile);
	*/
}

void State3::Update(float frameTime)
{
	//SceneManager::GetInstance()->Update(frameTime);//testing

	if (InputManager::GetInstance()->keyPressed & KEY_D)
	{
		StateManager::GetInstance()->m_GameStateStack.pop_back();
		StateManager::GetInstance()->AddState(StateManager::GetInstance()->GS_STATE_1);


		ResetInstance();
	}



}

void State3::Render()
{
	//SceneManager::GetInstance()->Render();
	//graphic engine
}

void State3::AddObjectInstance(ObjectInstance* objectInstance)
{
	m_StateOjectList.push_back(objectInstance);
}



State3* State3::GetInstance()
{
	if (!s_Instance)
		s_Instance = new State3();
	return s_Instance;
}

void State3::ResetInstance()
{
	for (auto p : m_StateOjectList)
	{
		delete p;
	}
	m_StateOjectList.clear();

	delete s_Instance;
	s_Instance = NULL;
	//SceneManager::GetInstance()->ResetInstance();
}

