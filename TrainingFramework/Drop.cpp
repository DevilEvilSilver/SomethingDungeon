#pragma once
#include"stdafx.h"
#include"Drop.h"
#include "Renderer.h"

Drop::Drop() {}

Drop::Drop(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

Drop::~Drop() 
{

}

void Drop::Update(float frameTime) {

}

void Drop::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}