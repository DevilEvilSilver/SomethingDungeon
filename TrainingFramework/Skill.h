#pragma once
#include "Object.h"
#include "Character.h"
#include "SkillId.h"
class Skill :
    public Object
{
protected:
    std::string m_EffectID;
    //USER
    Character* m_owner;
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
    void InitEffect(std::string prefabID);
    std::string DirectionPrefab(std::string ID,Vector2 dir);
    void SetDirectionPrefab(std::string ID, int index);
public:
    //MP COST
    
    // int mp_MPCost;
  
    bool m_isPlayer;
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

