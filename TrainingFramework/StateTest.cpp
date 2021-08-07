
#include "stdafx.h"
#include <algorithm> 
#include "Object.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

#include "InputManager.h"
#include "StateManager.h"
#include "SoundEngine.h"
#include "PhysicEngine.h"
#include "StateTest.h"




StateTest::StateTest()
{
	Init();
}

StateTest::~StateTest()
{
	for (auto a : m_ObjectList) {
		delete a;
	}
	m_ObjectList.clear();
	delete m_Camera;
}

void StateTest::Init()
{
	FILE* dataFile;
	dataFile = fopen(FILE_SM, "r");


	int iObjectCount;
	fscanf(dataFile, "#OBJECT_COUNT %d\n", &iObjectCount);

	while (iObjectCount--) {
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);

		char strPrefab[50];
		fscanf(dataFile, "PREFAB %s\n", &strPrefab);

		Matrix translation;
		GLfloat x, y, z;
		fscanf(dataFile, "POSITION %f, %f, %f\n", &x, &y, &z);
		translation.SetTranslation(x, y, z);

		Object* object = new Object(strPrefab, translation);
		AddObject(object);
	}

	float fLeft, fRight, fBottom, fTop;
	fscanf(dataFile, "#CAMERA\n");
	fscanf(dataFile, "PLANES %f, %f, %f, %f\n", &fLeft, &fRight, &fBottom, &fTop);
	float fNear;
	fscanf(dataFile, "NEAR %f\n", &fNear);
	float fFar;
	fscanf(dataFile, "FAR %f\n", &fFar);
	float fMovingSpeed;
	fscanf(dataFile, "MOVING SPEED %f\n", &fMovingSpeed);
	float fRotationSpeed;
	fscanf(dataFile, "ROTATION SPEED %f\n", &fRotationSpeed);
	m_Camera = new Camera(fLeft, fRight, fBottom, fTop, fNear, fFar, fMovingSpeed, fRotationSpeed);

	fclose(dataFile);
}

void StateTest::Update(float frameTime)
{
	m_Camera->Update(frameTime);

	for (auto& object : m_ObjectList) {
		object->Update(frameTime);
	}

	Control(frameTime);
	CheckCollision();
	DraggingObject();

}

void StateTest::Control(float frameTime)
{
	//testing

	//CHAR CONTROL
	if (InputManager::GetInstance()->keyPressed > 0) {
		
		float fSpeed = 5.0f;

		if (InputManager::GetInstance()->keyPressed & KEY_W)
		{
			m_ObjectList[1]->SetPosY(m_ObjectList[1]->GetPosY() + fSpeed * frameTime);
		}
		if (InputManager::GetInstance()->keyPressed & KEY_A)
		{
			m_ObjectList[1]->SetPosX(m_ObjectList[1]->GetPosX() - fSpeed * frameTime);
		}
		if (InputManager::GetInstance()->keyPressed & KEY_S)
		{
			m_ObjectList[1]->SetPosY(m_ObjectList[1]->GetPosY() - fSpeed * frameTime);
		}
		if (InputManager::GetInstance()->keyPressed & KEY_D)
		{
			m_ObjectList[1]->SetPosX(m_ObjectList[1]->GetPosX() + fSpeed * frameTime);
		}



		//CAMERA
		if (InputManager::GetInstance()->keyPressed & KEY_UP)
		{
			m_Camera->MoveUp(frameTime);
			//m_ObjectList[0]->SetPosY(m_ObjectList[0]->GetPosY() + fSpeed * frameTime);
		}
		if (InputManager::GetInstance()->keyPressed & KEY_LEFT)
		{
			m_Camera->MoveLeft(frameTime);
		}
		if (InputManager::GetInstance()->keyPressed & KEY_DOWN)
		{
			m_Camera->MoveDown(frameTime);
		}
		if (InputManager::GetInstance()->keyPressed & KEY_RIGHT)
		{
			m_Camera->MoveRight(frameTime);
		}


		//Play sound+STATE CHANGE
		if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
		{
			static bool isSoundPlayed = false;
			if (isSoundPlayed == false) {
				
				SoundEngine::GetInstance()->Play(0, 0.5, 1.5, true);
				isSoundPlayed = true;
			}

			StateManager::GetInstance()->ClosenAddState(StateManager::GetInstance()->GS_STATE_2);
			
		}


		//MOUSE
		if (InputManager::GetInstance()->keyPressed & MOUSE_LEFT)
		{
			Vector2 mousePosition = InputManager::GetInstance()->MousePosition(m_Camera);
			printf("move %.2f %.2f\n", mousePosition.x, mousePosition.y);
		}
		if (InputManager::GetInstance()->keyPressed & MOUSE_RIGHT)
		{

		}
	}

	//test attach cam to player
	m_Camera->SetPosition(Vector3(m_ObjectList[1]->GetPosX(), m_ObjectList[1]->GetPosY(), 0.0f));

	
}

void StateTest::DraggingObject()
{
	static Object* touched = NULL;

	if (InputManager::GetInstance()->keyPressed & (MOUSE_LEFT | MOUSE_RIGHT))
	{
		Vector2 mousePosition = InputManager::GetInstance()->MousePosition(m_Camera);
		if (touched == NULL) {
			for (auto a : m_ObjectList) {
				if (PhysicEngine::GetInstance()->CheckMouseRectangle(mousePosition, a) == true)
					touched = a;
			}
		}
		if (touched != NULL) {
			touched->SetPosX(mousePosition.x); touched->SetPosY(mousePosition.y);
		}
	}
	else
	{
		touched = NULL;
	}
}



void StateTest::CheckCollision()
{
	static bool isCollied = false;//test only

	bool testCheck = PhysicEngine::GetInstance()->CheckRectRectCollision(m_ObjectList[1], m_ObjectList[2]);


	if (isCollied == false && testCheck == true) {
		printf("Collied!\n");
		isCollied = true;
	}
	else if (isCollied == true && testCheck == false) {
		printf("Not Collied!\n");
		isCollied = false;
	}



}

void StateTest::Render()
{
	for (auto& obj : m_ObjectList) {
		obj->Render(this->m_Camera);
	}
}

void StateTest::AddObject(Object* object)
{
	m_ObjectList.push_back(object);
}

void StateTest::GetRenderOrder()
{
	std::sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object* a, Object* b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) < (b->GetPosY() - b->m_fHeight));
		});
}
