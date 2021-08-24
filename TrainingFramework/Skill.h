#pragma once
#include "Object.h"
#include "Character.h"
enum class SkillCoolDownTime {
    //ms
    BULLET_CDTIME = 100,
    AOE_CDTIME = 50,
    DASH_CDTIME = 500
};
enum class SkillMPCost {
    //
    AOE_MPCOST = 0,
    BULLET_MPCOST = 1,
    DASH_MPCOST = 0
};
enum class SkillExistingTime {
    //ms
    BULLET_EXISTINGTIME = 1000,
    AOE_EXISTINGTIME = 500,
};
enum class SkillDamage {
    //percent
    BULLET_DAMAGE = 150,
    AOE_DAMAGE = 100
};

class Skill :
    public Object
{
protected:

    //USER
    Character* m_owner;
    bool m_isPlayer;

    //DMG
    //SkillDamage m_percentDamage;
    SkillDamage m_SkillDamage;
    float m_damage;

    //EXIST TIME
    float m_currExistingTime;
    SkillExistingTime m_ExsitingTime;

    //KNOCKBACK
    bool m_isKnockBack;

    //hit flag
    bool m_bHit;

public:
    //MP COST
    bool isFinished;

    Skill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    virtual ~Skill();

    virtual void Init(Vector2 mousePos);

    void Update(float frameTime);
    void UpdateMove(float frameTime);         //Init Position and velocity
    virtual void UpdateHit(float frameTime);    // Hit-> Collison and Self Destruct
    void UpdateExistingTime(float frameTime);   // Self Destruct


    void Render(Camera* camera);
};

