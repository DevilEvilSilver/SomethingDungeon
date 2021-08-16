#pragma once
#include "Object.h"
#include "Character.h"

class Skill :
    public Object
{
protected:

    //USER
    Character* m_owner;
    bool m_isPlayer;

    //DMG
    //SkillDamage m_percentDamage;
    float m_percentDamage;
    float m_damage;

    //EXIST TIME
    float m_currExistingTime;
    float m_totalExsitingTime;
    //SkillExistingTime m_totalExsitingTime;

    //KNOCKBACK
    bool m_isKnockBack = false;
    
public:
    //MP COST
    int mp_MPCost;
  
    Skill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix);
    virtual ~Skill();

    virtual void Init(Vector2 mousePos);

    void Update(float frameTime);
    void UpdateMove(float frameTime);         //Init Position and velocity
    virtual void UpdateHit(float frameTime);    // Hit-> Collison and Self Destruct
    void UpdateExistingTime(float frameTime);   // Self Destruct
    
   
    void Render(Camera* camera);
    void Remove();
    

};

