#pragma once
#include "Enemy.h"
class Witch :
    public Enemy
{
public:
    Witch(std::string prefabID, Vector2 roomID, Matrix translationMatrix);

    void UniqueUpdate(float frameTime);

    void Shoot(Vector2 target);
    void Melee(Vector2 target);

	void createDrop();
};

