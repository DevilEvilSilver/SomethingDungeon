#pragma once
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
    BULLET_EXISTINGTIME = 3000,
    AOE_EXISTINGTIME = 800,
};
enum class SkillDamage {
    //percent
    BULLET_DAMAGE = 150,
    AOE_DAMAGE = 100
};