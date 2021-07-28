#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object() {}

Object::Object(unsigned int modelID, unsigned int shaderID, Matrix worldMatrix)
	: m_iModelID(modelID), m_iShaderID(shaderID), m_WorldMatrix(worldMatrix) {
	
}

Object::~Object() {

}

void Object::Update(float frameTime) {

}

void Object::Render(Camera *camera) {
	if (m_iTexture2DID.size() > 0)
		Renderer::GetInstance()->DrawTexture2D(this, camera);
}

Matrix Object::GetWorldMatrix() {
	return m_WorldMatrix;
}