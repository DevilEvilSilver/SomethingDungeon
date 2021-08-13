#pragma once
#include "Object.h"
#include "Character.h"
enum SkillCoolDownTime {
    // Milli second
    BULLET_COOLDOWN = 0,
    AOE_COOLDOWN = 1000
};
enum SkillMPCost {
    BULLET_MPCOST = 0,
    AOE_MPCOST = 1
};
enum SkillExistingTime {
    // Milli second
    BULLET_EXISTINGTIME = 5000,
    AOE_EXISTINGTIME = 200
};
enum SkillDamage {
    // Don vi %
    BULLET_DAMAGE = 100,
    AOE_DAMAGE = 150
};
class Skill :
    public Object
{
protected:
    Character* m_owner; // nguoi tao ra skill
    float m_damage;
    bool m_isPlayer;
    float m_currExistingTime;
    SkillExistingTime m_totalExsitingTime;
    SkillMPCost m_MPCost;
public:
    Skill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    virtual ~Skill();
    virtual void Update(float frameTime);
    virtual void UpdateHit(float frameTime);
    virtual void UpdateMove(float frameTime);
    void UpdateExistingTime(float frameTime);
    void Render(Camera* camera);
    void Remove();

};

