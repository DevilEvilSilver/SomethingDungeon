#pragma once
#include "Skill.h"
class AoeSkill :
    public Skill
{
public:
    float mp_fAoeRadius;

    AoeSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~AoeSkill();
    virtual void UpdateHit(float frameTime);
    virtual void Init(Vector2 mousePos);
};

