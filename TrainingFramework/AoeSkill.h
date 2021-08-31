#pragma once
#include "Skill.h"
class AoeSkill :
    public Skill
{
private:
    Vector2 m_offset;
public:
    float mp_fAoeRadius;

    AoeSkill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix, Vector2 target = {0,0});
    AoeSkill(Vector2  tar, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    ~AoeSkill();
    virtual void UpdateHit(float frameTime);
    virtual void Init(std::string ID,Vector2 target);
    void UpdateCurrPos(float frameTime);
};

