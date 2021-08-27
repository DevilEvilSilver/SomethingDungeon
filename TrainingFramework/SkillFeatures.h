#pragma once
enum class SkillCoolDownTime {
    //ms
    BULLET_PLAYER_CDTIME = 1000,
    BULLET_ENEMY_CDTIME = 5000,
    AOE_CDTIME = 360,
    DASH_CDTIME = 1000
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
    AOE_EXISTINGTIME = 360,
};
enum class SkillDamage {
    //percent
    BULLET_DAMAGE = 150,
    AOE_DAMAGE = 100
};