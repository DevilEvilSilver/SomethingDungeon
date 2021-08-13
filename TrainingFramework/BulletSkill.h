#pragma once
#include "Skill.h"
class BulletSkill :
    public Skill
{
    virtual void Update(float frameTime);
    virtual void UpdateHit(float frameTime);
    virtual void Move(float frameTime);
};

