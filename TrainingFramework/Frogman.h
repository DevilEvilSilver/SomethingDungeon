#pragma once
#include "Goblin.h"

class Frogman :
    public Goblin
{
public:
    Frogman(std::string prefabID, Vector2 roomID, Matrix translationMatrix);

    void UniqueUpdate(float frameTime);

    void Shoot(Vector2 target);
    void Melee(Vector2 target);

	void createDrop();
}
;