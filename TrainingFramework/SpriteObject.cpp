#include "stdafx.h"
#include "SpriteObject.h"
#include "Renderer.h"
#include "Vertex.h"

SpriteObject::SpriteObject() {}

SpriteObject::SpriteObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix,
	GLfloat width, GLfloat height)
	: Object(modelID, shaderID, translationMatrix, rotationMatrix, scaleMatrix), m_fWidth(width), m_fHeight(height),
	m_strState("mainIdleLeft"), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {

}

SpriteObject::~SpriteObject() {

}

void SpriteObject::Update(float frameTime) { 
	m_fCurrFrameTime += frameTime;
}

void SpriteObject::Render(Camera *camera) {
	Renderer::GetInstance()->DrawSprite(this, camera);
}