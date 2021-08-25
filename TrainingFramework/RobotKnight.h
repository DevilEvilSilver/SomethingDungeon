#pragma once
#include "Enemy.h"
class RobotKnight :
    public Enemy
{
public:

    enum BossState
    {
        BS_NORMAL,
        BS_CHARGE,
        BS_ATTACK1,
        BS_ATTACK2,
        BS_GUARD
    };

    BossState m_bState = BS_NORMAL;
    Vector2 m_target = Vector2(0, 0);

    float totalAtkCD = 1.0f;
    float currAtkCD = 0.0f;


    RobotKnight(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    
    void UniqueUpdate(float frameTime);

    void Normal(float frameTime);
    void Charge(float frameTime);
    void Attack1(float frameTime);
    void Attack2(float frameTime);
    void Guard(float frameTime);
    void SetBS(BossState bs);

    void Shoot(Vector2 target);
    void Melee(Vector2 target);


};

