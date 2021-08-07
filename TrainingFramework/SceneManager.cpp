#include "stdafx.h"
#include "SceneManager.h"


SceneManager * SceneManager::s_Instance = NULL;

SceneManager::SceneManager(void) {
	this->Init();
}

SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new SceneManager();
	return s_Instance;
}



void SceneManager::Init() {
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

		Object *object = new Object(strPrefab, translation);
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

void SceneManager::CheckCollision()
{
	//static bool isCollied = false;//test only
	//
	//bool testCheck=PhysicEngine::GetInstance()->CheckRectRectCollision(m_ObjectList[1], m_ObjectList[2]);
	//
	//
	//if (isCollied==false&&testCheck == true) {
	//	printf("Collied!\n");
	//	isCollied = true;
	//}
	//else if (isCollied == true && testCheck == false) {
	//	printf("Not Collied!\n");
	//	isCollied = false;
	//}
	/*****************************TienDollars_Code********************************/
	
	
}

void SceneManager::Render() {
	//GetRenderOrder();
	for (auto& obj : m_ObjectList) {
		obj->Render(this->m_Camera);
	}
	
}

void SceneManager::Update(float frameTime) {
	m_Camera->Update(frameTime);
	UpdateControl(frameTime);
	CollisionManager::UpdateCollision(frameTime);
	for (auto& object : m_ObjectList) {
		object->Update(frameTime);
	}
	
}

void SceneManager::UpdateControl(float frameTime)
{
	
	float fSpeed = 20.0f;
	static int lastKey = 0;
	int newKeyPressed = InputManager::GetInstance()->keyPressed;
	if ((newKeyPressed & KEY_W))
	{
		m_ObjectList[0]->SetVelocityY(fSpeed);
	}
	else if (newKeyPressed & KEY_S )
	{
		m_ObjectList[0]->SetVelocityY(-fSpeed);
	}
	else
		m_ObjectList[0]->SetVelocityY(0);
	if ((newKeyPressed & KEY_A))
	{
		m_ObjectList[0]->SetVelocityX(-fSpeed);
	}
	else if (newKeyPressed & KEY_D)
	{
		m_ObjectList[0]->SetVelocityX(fSpeed);
	}
	else
		m_ObjectList[0]->SetVelocityX(0);
	
	
	lastKey = newKeyPressed;
	//CAMERA
	if (InputManager::GetInstance()->keyPressed & KEY_UP)
	{
		m_Camera->MoveUp(frameTime);
		
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


	//STATE CHANGE
	if (InputManager::GetInstance()->keyPressed & KEY_SPACE)
	{
		StateManager::GetInstance()->m_GameStateStack.pop_back();
		StateManager::GetInstance()->AddState(StateManager::GetInstance()->GS_STATE_2);
	}

}

void SceneManager::AddObject(Object *object) {
	m_ObjectList.push_back(object);
}

void SceneManager::GetRenderOrder() {
	std::sort(m_ObjectList.begin(), m_ObjectList.end(), [](Object *a, Object *b) -> bool {
		return ((a->GetPosY() - a->m_fHeight) < (b->GetPosY() - b->m_fHeight));
	});
}

void SceneManager::ResetInstance() {
	
	for (auto& object : m_ObjectList) {
		delete object;
	}
	m_ObjectList.clear();
	delete m_Camera;
	

	delete s_Instance;
	s_Instance = NULL;
}