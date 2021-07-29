#include "stdafx.h"
#include "SpriteObject.h"
#include "Renderer.h"
#include "Vertex.h"

SpriteObject::SpriteObject() {}

SpriteObject::SpriteObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix,
	unsigned int type, float posX, float posY, float width, float height, float radius)
	: Object(modelID, shaderID, translationMatrix, rotationMatrix, scaleMatrix, type, posX, posY, width, height, radius),
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