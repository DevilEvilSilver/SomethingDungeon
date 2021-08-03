#include "stdafx.h"
#include "State1.h"
#include "StateManager.h"

#include "ObjectInstance.h"
#include "InputManager.h"
//#include "SceneManager.h"

#include "Camera.h"

State1* State1::s_Instance = NULL;

State1::State1()
{
	Init();
	//SceneManager::GetInstance();	//testing
}

State1::~State1()
{
}


void State1::Init()
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

void State1::Update(float frameTime)
{
	//Add new state:				Stm:AddState( )
	//Close and Add new state:		pop + Stm:AddState + Reset( )
	//Close:						pop + Reset( )

	//SceneManager::GetInstance()->Update(frameTime);//testing


	if (InputManager::GetInstance()->keyPressed & KEY_A)
	{
		StateManager::GetInstance()->m_GameStateStack.pop_back();
		StateManager::GetInstance()->AddState(StateManager::GetInstance()->GS_STATE_2);


		ResetInstance();
	}



}

void State1::Render()
{
	//graphic engine
	//SceneManager::GetInstance()->Render();	//testing
}

void State1::AddObjectInstance(ObjectInstance* objectInstance)
{
	m_StateOjectList.push_back(objectInstance);
}



State1* State1::GetInstance()
{
	if (!s_Instance)
		s_Instance = new State1();
	return s_Instance;
}

void State1::ResetInstance()
{
	for (auto p : m_StateOjectList)
	{
		delete p;
	}
	m_StateOjectList.clear();

	delete s_Instance;
	s_Instance = NULL;

	//SceneManager::GetInstance()->ResetInstance();	//testing
}

