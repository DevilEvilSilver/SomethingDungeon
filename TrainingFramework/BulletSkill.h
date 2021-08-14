#pragma once
#include "Skill.h"
class BulletSkill :
    public Skill
{
public:
    BulletSkill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~BulletSkill();
    virtual void Update(float frameTime);
    virtual void UpdateHit(float frameTime);
    virtual void Init();
};

