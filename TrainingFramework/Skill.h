#pragma once
#include "Object.h"
#include "Character.h"
enum class SkillCoolDownTime {
    // Milli second
    BULLET_COOLDOWN = 0,
    AOE_COOLDOWN = 1000
};
enum class SkillMPCost {
    BULLET_MPCOST = 0,
    AOE_MPCOST = 1
};
enum class SkillExistingTime {
    // Milli second
    BULLET_EXISTINGTIME = 5000,
    AOE_EXISTINGTIME = 100
};
enum class SkillDamage {
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
    SkillDamage m_percentDamage;
public:
    SkillMPCost mp_MPCost;
    Skill(Vector2 mousePos, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    virtual ~Skill();
    virtual void UpdateHit(float frameTime);    // Hit-> Collison and Self Destruct
    virtual void Init(Vector2 mousePos);
    void UpdateExistingTime(float frameTime);   // Self Destruct
    void UpdateMove(float frameTime);         //Init Position and velocity
    void Update(float frameTime);
    void Render(Camera* camera);
    void Remove();
    

};

