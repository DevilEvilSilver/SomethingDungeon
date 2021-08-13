#pragma once
#include "Skill.h"
class AoeSkill :
    public Skill
{
public:
    AoeSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~AoeSkill();
    virtual void Update(float frameTime);
    virtual void UpdateHit(float frameTime);
    virtual void UpdateMove(float frameTime);
};

