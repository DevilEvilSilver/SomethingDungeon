#include "stdafx.h"
#include "AnimatedObject.h"
#include "Renderer.h"
#include "Vertex.h"

AnimatedObject::AnimatedObject() {}

//AnimatedObject::AnimatedObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix,
//	unsigned int type, float posX, float posY, float width, float height, float radius)
//	: Object(modelID, shaderID, translationMatrix, rotationMatrix, scaleMatrix, type, posX, posY, width, height, radius),
//	m_strState("mainIdleLeft"), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {
//
//}

AnimatedObject::~AnimatedObject() {

}

void AnimatedObject::Update(float frameTime) { 
	m_fCurrFrameTime += frameTime;
}

void AnimatedObject::Render(Camera *camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}