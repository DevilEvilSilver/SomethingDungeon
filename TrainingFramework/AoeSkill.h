#pragma once
#include "Skill.h"
class AoeSkill :
    public Skill
{
public:
    float mp_fAoeRadius;

    AoeSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix, Vector2 target = {0,0});
    AoeSkill(Vector2  tar, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~AoeSkill();
    virtual void UpdateHit(float frameTime);
    virtual void Init(Vector2 target);
};

