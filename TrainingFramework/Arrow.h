#pragma once
#include "Trap.h"
#include "ArrowTower.h"

class Arrow : public Trap {
private: 
    int m_iAttack ;
   
    //bool isCollide;
public:
    int dir = 1;
    //Vector2 mp_dir;
    Arrow::Arrow(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~Arrow();
    void Update(float frameTime);

   // void UpdateGotHit();
};