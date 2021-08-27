#pragma once
#include "Goblin.h"

class Orcman :
    public Goblin
{
public:
    Orcman(std::string prefabID, Vector2 roomID, Matrix translationMatrix);

    void UniqueUpdate(float frameTime);

    void Shoot(Vector2 target);
    void Melee(Vector2 target);

}
;