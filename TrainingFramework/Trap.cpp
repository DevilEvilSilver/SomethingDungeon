#include"stdafx.h"
#include"Trap.h"
#include "Renderer.h"

Trap::Trap() {}

Trap::Trap(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Object(prefabID, roomID, translationMatrix) {

}

Trap::~Trap()
{

}

void Trap::Update(float frameTime) {

}



