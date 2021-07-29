#include "stdafx.h"
#include <algorithm> 
#include "SceneManager.h"
#include "AnimatedObject.h"
#include "StaticObject.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

SceneManager * SceneManager::s_Instance = NULL;

SceneManager::SceneManager(void) {
	this->Init();
}

SceneManager::~SceneManager() {
	for (auto& object : m_ObjectList) {
		delete object;
	}
	m_ObjectList.resize(0);
	delete m_Camera;
}

SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new SceneManager();
	return s_Instance;
}

void SceneManager::ResetInstance() {
	delete s_Instance;
	s_Instance = NULL;
}

void SceneManager::Init() {
	FILE* dataFile;
	dataFile = fopen(FILE_SM, "r");

	int iAnimatedCount;
	fscanf(dataFile, "#ANIMATED_OBJECT_COUNT %d\n", &iAnimatedCount);

	while (iAnimatedCount--) {
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);

		unsigned int iModel;
		fscanf(dataFile, "MODEL %d\n", &iModel);

		unsigned int iShader;
		fscanf(dataFile, "SHADER %d\n", &iShader);

		char strType[50];
		unsigned int iType;
		GLfloat fPosX, fPosY, fWidth = 0.0f, fHeight = 0.0f, fRadius = 0.0f;
		fscanf(dataFile, "TYPE %s\n", &strType);
		if (!strcmp(strType, "RECT")) {
			iType = RECTANGLE;
			fscanf(dataFile, "COORD %f, %f, %f, %f\n", &fPosX, &fPosY, &fWidth, &fHeight);
		}
		else if (!strcmp(strType, "CIRCLE")) {
			iType = CIRCLE;
			fscanf(dataFile, "COORD %f, %f, %f\n", &fPosX, &fPosY, &fRadius);
		}

		Matrix translation, rotationX, rotationY, rotationZ, scale, worldMatrix;
		GLfloat x, y, z;
		fscanf(dataFile, "POSITION %f, %f, %f\n", &x, &y, &z);
		translation.SetTranslation(x, y, z);
		fscanf(dataFile, "ROTATION %f, %f, %f\n", &x, &y, &z);
		rotationX.SetRotationX(x); 
		rotationY.SetRotationY(y);
		rotationZ.SetRotationZ(z);
		fscanf(dataFile, "SCALE %f, %f, %f\n", &x, &y, &z);
		scale.SetScale(x, y, z);

		Object *object = new AnimatedObject(iModel, iShader, translation, rotationZ * rotationX * rotationY, scale, 
			iType, fPosX, fPosY, fWidth, fHeight, fRadius);
		AddObject(object);
	}

	int iStaticCount;
	fscanf(dataFile, "#STATIC_OBJECT_COUNT %d\n", &iStaticCount);

	while (iStaticCount--) {
		unsigned int id;
		fscanf(dataFile, "ID %d\n", &id);

		unsigned int iModel;
		fscanf(dataFile, "MODEL %d\n", &iModel);

		unsigned int iTextureCount;
		fscanf(dataFile, "TEXTURE_COUNT %d\n", &iTextureCount);
		unsigned int iTmpTextureCount = iTextureCount; //backup texture count
		std::vector<unsigned int> aiTexture;
		while (iTextureCount--) {
			unsigned int textureID;
			fscanf(dataFile, "TEXTURE %d\n", &textureID);
			aiTexture.push_back(textureID);
		}

		unsigned int iShader;
		fscanf(dataFile, "SHADER %d\n", &iShader);

		char strType[50];
		unsigned int iType;
		GLfloat fPosX, fPosY, fWidth = 0.0f, fHeight = 0.0f, fRadius = 0.0f;
		fscanf(dataFile, "TYPE %s\n", &strType);
		if (!strcmp(strType, "RECT")) {
			iType = RECTANGLE;
			fscanf(dataFile, "COORD %f, %f, %f, %f\n", &fPosX, &fPosY, &fWidth, &fHeight);
		}
		else if (!strcmp(strType, "CIRCLE")) {
			iType = CIRCLE;
			fscanf(dataFile, "COORD %f, %f, %f\n", &fPosX, &fPosY, &fRadius);
		}

		Matrix translation, rotationX, rotationY, rotationZ, scale, worldMatrix;
		GLfloat x, y, z;
		fscanf(dataFile, "POSITION %f, %f, %f\n", &x, &y, &z);
		translation.SetTranslation(x, y, z);
		fscanf(dataFile, "ROTATION %f, %f, %f\n", &x, &y, &z);
		rotationX.SetRotationX(x);
		rotationY.SetRotationY(y);
		rotationZ.SetRotationZ(z);
		fscanf(dataFile, "SCALE %f, %f, %f\n", &x, &y, &z);
		scale.SetScale(x, y, z);
		worldMatrix = scale * rotationZ * rotationX * rotationY * translation;

		float fTextureScale;
		fscanf(dataFile, "TEXTURE_SCALE %f\n", &fTextureScale);

		Object *object = new StaticObject(iModel, iShader, translation, rotationZ * rotationX * rotationY, scale,
			iType, fPosX, fPosY, fWidth, fHeight, fRadius, aiTexture, fTextureScale);
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

void SceneManager::Render() {
	GetRenderOrder();
	for (auto& obj : m_ObjectList) {
		obj->Render(this->m_Camera);
	}
}

void SceneManager::Update(float frameTime) {
	m_Camera->Update(frameTime);

	for (auto& object : m_ObjectList) {
		object->Update(frameTime);
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