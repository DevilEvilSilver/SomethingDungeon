#pragma once
#include"Witch.h"

class CPlant : public Witch {

public:

    CPlant(std::string prefabID, Vector2 roomID, Matrix translationMatrix);

    void UniqueUpdate(float frameTime);

   void Shoot(Vector2 target);
    void Melee(Vector2 target);

};