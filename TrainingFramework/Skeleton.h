#pragma once
#include "Enemy.h"
class Skeleton :
    public Enemy
{
public:
    Skeleton(std::string prefabID, Vector2 roomID, Matrix translationMatrix);

    void UniqueUpdate(float frameTime);

    void Shoot(Vector2 target);
    void Melee(Vector2 target);
};

