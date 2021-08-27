#pragma once
#include "Object.h"
#include "Character.h"
enum class EffectExistingTime {
    //SKILL
    SKILL_FREEZE1 = 400,
    SKILL_FREEZE2 = 400,
    SKILL_FREEZE3 = 400,

    SKILL_FIRE1     = 300,
    SKILL_FIRE2     = 300,
    SKILL_FIRE3     = 300
};
class Effect :
    public Object
{
private:
    float m_fExistingTime;
    float m_fCurrExistingTime;
    Character* m_Victim;
public:
    bool mp_isFisnished;
    Effect(Vector2 pos, EffectExistingTime existTime, std::string prefabID, Vector2 roomID, Matrix translationMatrix, Character* victim = NULL);
    ~Effect();
    void Update(float frameTime);
    void UpdateExistingTime(float frameTime);
    void UpdatePosition(float frametime);
    void Init(Vector2 pos);
};

