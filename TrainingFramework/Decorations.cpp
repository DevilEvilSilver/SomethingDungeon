#include "stdafx.h"
#include "Decorations.h"

Decorations::Decorations(std::string prefabID, Vector2 roomID, Matrix translationMatrix):
	 Object(prefabID, roomID, translationMatrix)
{
}

Decorations::~Decorations()
{
}
