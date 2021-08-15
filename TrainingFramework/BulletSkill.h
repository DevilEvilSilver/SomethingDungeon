#pragma once
#include "Skill.h"
class BulletSkill :
    public Skill
{
public:
    Vector2 mp_dir;
    BulletSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~BulletSkill();
    virtual void UpdateHit(float frameTime);
    virtual void Init(Vector2 mousePos);
};

