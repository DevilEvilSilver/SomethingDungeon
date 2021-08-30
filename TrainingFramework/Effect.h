#pragma once
#include "Object.h"
#include "Character.h"
enum class EffectExistingTime {
    //SKILL
    EFFECT_EXISTINGTIME_FREEZE1 = 400,
    EFFECT_EXISTINGTIME_FREEZE2 = 400,
    EFFECT_EXISTINGTIME_FREEZE3 = 400,

    EFFECT_EXISTINGTIME_FIRE1 = 300,
    EFFECT_EXISTINGTIME_FIRE2 = 300,
    EFFECT_EXISTINGTIME_FIRE3 = 300,

    EFFECT_SKILL_EXISTINGTIME = 450     //dung chung cho moi effect skill
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

