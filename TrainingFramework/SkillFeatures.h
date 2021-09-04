#pragma once
enum class SkillCoolDownTime {
    //ms
    BULLET_PLAYER_CDTIME = 1000,
    BULLET_ENEMY_CDTIME = 5000,
    AOE_CDTIME = 500,
    DASH_CDTIME = 750,

    SKILL_FIRE_LV1_CDTIME = 700,
    SKILL_FIRE_LV2_CDTIME = 500,
    SKILL_FIRE_LV3_CDTIME = 1000,

    SKILL_FREEZE_LV1_CDTIME = 700,
    SKILL_FREEZE_LV2_CDTIME = 700,
    SKILL_FREEZE_LV3_CDTIME = 1200
};
enum class SkillMPCost {
    //
    AOE_MPCOST = 0,
    BULLET_MPCOST = 1,
    DASH_MPCOST = 0,

    SKILL_FIRE_LV1_MPCOST = 0,
    SKILL_FIRE_LV2_MPCOST = 0,
    SKILL_FIRE_LV3_MPCOST = 0,

    SKILL_FREEZE_LV1_MPCOST = 3,
    SKILL_FREEZE_LV2_MPCOST = 4,
    SKILL_FREEZE_LV3_MPCOST = 6
};
enum class SkillExistingTime {
    //ms
    BULLET_EXISTINGTIME = 3000,
    AOE_EXISTINGTIME = 360,

    SKILL_FIRE_LV1_EXISTINGTIME = 360,
    SKILL_FIRE_LV2_EXISTINGTIME = 360,
    SKILL_FIRE_LV3_EXISTINGTIME = 360,

    SKILL_FREEZE_LV1_EXISTINGTIME = 2000,
    SKILL_FREEZE_LV2_EXISTINGTIME = 2000,
    SKILL_FREEZE_LV3_EXISTINGTIME = 2000,

};
enum class SkillDamage {
    //percent
    BULLET_DAMAGE = 150,
    AOE_DAMAGE = 100,

    SKILL_FIRE_LV1_DMG = 100,
    SKILL_FIRE_LV2_DMG = 60,
    SKILL_FIRE_LV3_DMG = 220,

    SKILL_FREEZE_LV1_DMG = 150,
    SKILL_FREEZE_LV2_DMG = 175,
    SKILL_FREEZE_LV3_DMG = 250,
};