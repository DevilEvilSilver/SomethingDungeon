#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object() {}

Object::Object(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix)
	: m_iModelID(modelID), m_iShaderID(shaderID), m_TranslationMatrix(translationMatrix), m_RotationMatrix(rotationMatrix), m_ScaleMatrix(scaleMatrix), m_isNewWorld(true) {
	
}

Object::~Object() {

}

void Object::Update(float frameTime) {

}

void Object::Render(Camera *camera) {
	//if (m_iTexture2DID.size() > 0)
	//	Renderer::GetInstance()->DrawTexture2D(this, camera);
}

Matrix Object::GetWorldMatrix() {
	if (m_isNewWorld) {
		m_WorldMatrix = m_ScaleMatrix * m_RotationMatrix * m_TranslationMatrix;
		m_isNewWorld = false;
	}
	return m_WorldMatrix;
}

float Object::GetPosX() {
	return m_TranslationMatrix.m[3][0];
}

float Object::GetPosY() {
	return m_TranslationMatrix.m[3][1];
}

void Object::SetPosX(float x) {
	m_TranslationMatrix.m[3][0] = x;
	m_isNewWorld = true;
}

void Object::SetPosY(float y) {
	m_TranslationMatrix.m[3][1] = y;
	m_isNewWorld = true;
}
