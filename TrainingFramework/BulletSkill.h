#pragma once
#include "Skill.h"
class BulletSkill :
    public Skill
{
public:
    Vector2 mp_dir;
    BulletSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~BulletSkill();
    virtual void UpdateHit(float frameTime);
    virtual void Init();
};

