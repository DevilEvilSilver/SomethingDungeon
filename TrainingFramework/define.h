#pragma once

//SYSTEM
#define SCREEN_W					1080.0f
#define SCREEN_H					720.0f

#define LIMIT_FPS					120

#define PI							3.14159265f
#define HALFPI						(PI/2.0f)

#define ROTATION_LOCK				85.0f

#define VERTEX_OFFSET_POS			0
#define VERTEX_OFFSET_NORM			(1 * sizeof(Vector3))
#define VERTEX_OFFSET_BINORM		(2 * sizeof(Vector3))
#define VERTEX_OFFSET_TGT			(3 * sizeof(Vector3))
#define VERTEX_OFFSET_UV			(4 * sizeof(Vector3))

//INIT STATE
	//STATES FILE
#define FILE_S_LOAD						"../Resources/States/S_LOAD.txt"
#define FILE_R_LOAD						"../Resources/States/R_LOAD.txt"
#define FILE_SD_LOAD					"../Resources/States/SD_LOAD.txt"
#define FILE_S_LOGO						"../Resources/States/S_LOGO.txt"
#define FILE_R_LOGO						"../Resources/States/R_LOGO.txt"
#define FILE_SD_LOGO					"../Resources/States/SD_LOGO.txt"
#define FILE_S_WELCOME					"../Resources/States/S_WELCOME.txt"
#define FILE_R_WELCOME					"../Resources/States/R_WELCOME.txt"
#define FILE_SD_WELCOME					"../Resources/States/SD_WELCOME.txt"
#define FILE_S_PLAY						"../Resources/States/S_PLAY.txt"

#define FILE_R_PLAY_1					"../Resources/States/R_PLAY_1.txt"
#define FILE_R_PLAY_2					"../Resources/States/R_PLAY_2.txt"
#define FILE_R_PLAY_3					"../Resources/States/R_PLAY_3.txt"

#define FILE_SD_PLAY					"../Resources/States/SD_PLAY.txt"
#define FILE_S_SHOP						"../Resources/States/S_SHOP.txt"
#define FILE_R_SHOP						"../Resources/States/R_SHOP.txt"
#define FILE_SD_SHOP					"../Resources/States/SD_SHOP.txt"
#define FILE_S_RESULT					"../Resources/States/S_RESULT.txt"
#define FILE_R_RESULT					"../Resources/States/R_RESULT.txt"
#define FILE_SD_RESULT					"../Resources/States/SD_RESULT.txt"
#define FILE_S_INSTRUCTION				"../Resources/States/S_INSTRUCTION.txt"
#define FILE_R_INSTRUCTION				"../Resources/States/R_INSTRUCTION.txt"
#define FILE_SD_INSTRUCTION				"../Resources/States/SD_INSTRUCTION.txt"
#define FILE_S_CREDIT					"../Resources/States/S_CREDIT.txt"
#define FILE_R_CREDIT					"../Resources/States/R_CREDIT.txt"
#define FILE_SD_CREDIT					"../Resources/States/SD_CREDIT.txt"

	//FILE RECORD
#define FILE_RECORD						"../Resources/record.txt"
#define FLOOR_1							"FLOOR_1"
#define FLOOR_2							"FLOOR_2"
#define FLOOR_3							"FLOOR_3"
#define FLOOR_BOSS						"FLOOR_BOSS"
#define RECORD_WIN						"WIN"
#define RECORD_LOSE						"LOSE"
#define INIT_PLAYER_HP					10
#define INIT_PLAYER_MP					10
#define INIT_PLAYER_ATK					3
#define INIT_PLAYER_DEF					3
#define INIT_PLAYER_GOLD				10
#define INIT_PLAYER_KEY					0
#define INIT_PLAYER_SPEED				3.0f
#define INIT_PLAYER_MELEE				"skillFireLv1"
#define INIT_PLAYER_RANGE				"skillFreezeLv1"
#define PLAYER_ATK_MAX					10
#define PLAYER_DEF_MAX					10
#define PLAYER_SPEED_MAX				10

//MAP
#define MAP_WIDTH					22
#define MAP_HEIGHT					22
#define MAP_MAX_TUNNEL				65
#define TUNNEL_MAX_LENGTH			7
#define ROOM_WIDTH					9
#define ROOM_HEIGHT					6
#define PLAYER_START_POSX			10.0
#define PLAYER_START_POSY			10.0

//INPUT
#define KEY_W		1<<0
#define KEY_A		1<<1
#define KEY_S		1<<2
#define KEY_D		1<<3
#define KEY_UP		1<<4
#define KEY_LEFT	1<<5
#define KEY_DOWN	1<<6
#define KEY_RIGHT	1<<7
#define KEY_SPACE	1<<8
#define MOUSE_LEFT	1<<29
#define MOUSE_RIGHT	1<<30

//PHYSIC ENGINE
#define RECTANGLE					0
#define CIRCLE						1
#define RECTBOUND					2
#define Y_EPSILON			        0.5
#define X_EPSILON			        0.1

//FONT
#define FONT_SOLID				1
#define FONT_DOGICA				0
#define FONT_DOGICA_BOLD		2
#define FONT_BANK				3
#define FONT_BANK_BOLD			4

//SHADER
#define SHADER_SPRITE			0
#define SHADER_TEXT				1

//PREFAB
#define DEATH_BANNER	"deathBanner"
#define TRANSISTION		"transition"
#define GATE			"gate"
#define PLAYER			"mainChar"
#define ENEMY			"enemy"
#define SKILL			"skill"
#define SKILL_2			"skill2"
#define BULLET_SKILL	"skill"
#define AOE_SKILL		"enemyAoeskill"
//ENEMY HP MOB
#define ENEMY_HPMOB		"enemyHpMob"
#define ENEMY_HPMOB_BOUND	"enemyHpMobBound"
	//SKILL PREFAB
#define SKILL_WIND1		"skillWind1"
#define SKILL_WIND2		"skillWind2"
#define SKILL_WIND3		"skillWind3"

#define SKILL_FIRE1			"skillFireLv1"
#define SKILL_FIRE10		"skillFireLv10"
#define SKILL_FIRE11		"skillFireLv11"
#define SKILL_FIRE12		"skillFireLv12"
#define SKILL_FIRE13		"skillFireLv13"
#define SKILL_FIRE14		"skillFireLv14"

#define SKILL_FIRE2			"skillFireLv2"
#define SKILL_FIRE20		"skillFireLv20"
#define SKILL_FIRE21		"skillFireLv21"
#define SKILL_FIRE22		"skillFireLv22"
#define SKILL_FIRE23		"skillFireLv23"
#define SKILL_FIRE24		"skillFireLv24"

#define SKILL_FIRE3			"skillFireLv3"
#define SKILL_FIRE30		"skillFireLv30"
#define SKILL_FIRE31		"skillFireLv31"
#define SKILL_FIRE32		"skillFireLv32"
#define SKILL_FIRE33		"skillFireLv33"
#define SKILL_FIRE34		"skillFireLv34"

#define SKILL_FREEZE1		"skillFreezeLv1"
#define SKILL_FREEZE10		"skillFreezeLv10"
#define SKILL_FREEZE11		"skillFreezeLv11"
#define SKILL_FREEZE12		"skillFreezeLv12"
#define SKILL_FREEZE13		"skillFreezeLv13"
#define SKILL_FREEZE14		"skillFreezeLv14"

#define SKILL_FREEZE2		"skillFreezeLv2"
#define SKILL_FREEZE20		"skillFreezeLv20"
#define SKILL_FREEZE21		"skillFreezeLv21"
#define SKILL_FREEZE22		"skillFreezeLv22"
#define SKILL_FREEZE23		"skillFreezeLv23"
#define SKILL_FREEZE24		"skillFreezeLv24"

#define SKILL_FREEZE3		"skillFreezeLv3"	//notprefabId, to distinguish to the others
#define SKILL_FREEZE30		"skillFreezeLv30"
#define SKILL_FREEZE31		"skillFreezeLv31"
#define SKILL_FREEZE32		"skillFreezeLv32"
#define SKILL_FREEZE33		"skillFreezeLv33"
#define SKILL_FREEZE34		"skillFreezeLv34"

#define NORMAL_ROOM		"normalRoom"
#define NORMAL_ROOM_1	"normalRoom1"
#define NORMAL_ROOM_2	"normalRoom2"
#define NORMAL_ROOM_3	"normalRoom3"
#define NORMAL_ROOM_4	"normalRoom4"
#define NORMAL_ROOM_5	"normalRoom5"

#define WALL_ROOM		"wallRoom"
#define BORDER_ROOM		"borderRoom"

#define BORDER_ROOM_1_1	"borderRoom_1_1"
#define BORDER_ROOM_1_2	"borderRoom_1_2"
#define BORDER_ROOM_1_3	"borderRoom_1_3"
#define BORDER_ROOM_1_4	"borderRoom_1_4"
	//OBJECT
#define KEY				"key"
#define GOLD			"gold"
#define HP_PO			"hpPo"
#define MP_PO			"mpPo"
#define SPIKE_TRAP		"spikeTrap"
#define BOMB_TRAP		"bombTrap"

#define TREASURE		"treasure"
#define TOWER			"tower"
	//DECO
#define DOUBLE_BARRELS  "doubleBarrels"
#define TRIO_BARRELS	"trioBarrels"
#define BROKEN_WALL		"brokenWall"
#define POLE_1			"pole_1"
#define POLE_2			"pole_2"
#define POLE_3			"pole_3"
#define POLE_4			"pole_4"

#define BOX				"box"
#define BROKEN_COFFIN	"brokenCoffin"
#define BROKEN_COFFIN_2	"brokenCoffin2"
#define NORMAL_VASE		"normalVase"
#define BROKEN_VASE		"brokenVase"
#define FLOOR3_POLE_1	"pole_1"
#define FLORR3_POLE_2	"pole_2"
//FLR 2
#define F2_ROCK			"rock"
#define F2_POLE_1		"pole_1"
#define F2_POLE_2		"pole_2"
#define F2_POLE_3		"pole_3"
#define F2_POLE_4		"pole_4"
#define F2_TOMB_1		"tomb_1"
#define F2_TOMB_2		"tomb_2"
#define F2_WELL			"well"
#define F2_TREE_1		"tree_1"
#define F2_TREE_2		"tree_2"
#define F2_TREE_3		"tree_3"


	//ENEMY
#define WITCH			"violetWitch"
#define B_ROBOTKNIGHT	"robotKnight"
#define SKELETON		"skeleton"
#define PLANT			"carnivorousPlant"
#define BEAR			"meleeSoldier"
#define FROGMAN			"frogman"
#define ORCMAN			"orcman"
#define C_PLANT			"carnivorousPlant"

#define CHEST			"chest"
#define ARROW_TOWER		"arrowTower"
	//UI
#define ICON_FLAME_SWORD	"meleeIcon1"
#define ICON_PYRO_WAVE		"meleeIcon2"
#define ICON_SOLAR_DESCEND	"meleeIcon3"
#define ICON_ICE_ARROW		"rangeIcon1"
#define ICON_GLACIAL_BLAST	"rangeIcon2"
#define ICON_ABSOLUTE_ZERO	"rangeIcon3"

#define MINIMAP_MAP		"minimap"
#define MINIMAP_PLAYER	"minimapPlayer"
#define MINIMAP_BOUND	"minimapBound"

	//EFFECT
#define EFFECT_SKILL_FREEZE1 "skillEffectFreeze1"
#define EFFECT_SKILL_FREEZE2 "skillEffectFreeze2"
#define EFFECT_SKILL_FREEZE3 "skillEffectFreeze3"
#define EFFECT_SKILL_FIRE1 "skillEffectFire1"
#define EFFECT_SKILL_FIRE2 "skillEffectFire2"
#define EFFECT_SKILL_FIRE3 "skillEffectFire3"
//#define EFFECT_SKILL_WIND1 "skillEffectWind1"
//#define EFFECT_SKILL_WIND2 "skillEffectWind2"
//#define EFFECT_SKILL_WIND3 "skillEffectWinf3"
//#define EFFECT_SKILL_WIND4 "skillEffectWind4"


//SKILL
#define	BULLET_SPEED	10

//ANIMATION
#define INIT_ANIM		"init"

	//CHARACTER
#define IDLE_LEFT		"idleLeft"
#define MOVE			"move"
#define DASH			"dash"
#define GOTHIT			"gothit"
#define ATTACK			"attack"
#define DEATH			"death"

	//BUTTON
#define B_NORMAL			"normal"
#define B_PRESSED			"pressed"
#define B_HOVER				"hover"
#define B_UNAVAILABLE		"unavailable"

	//DROP
#define KEY_SPIN		"keyspin"
#define GOLD_SPIN		"goldspin"
#define HP_POTION		"hpPotion"
#define MP_POTION		"mpPotion"

	//TRAP
#define GATE_COLLIDE	"gateCollide"
#define GATE_ACTIVE		"gateActive"
#define BOMB_INIT		"bombInit"
#define BOOMED			"boomed"
#define SPIKE			"spike"

	//RESULT
#define WIN_BG			"winBG"
#define WIN_TITLE		"winTitle"
#define LOSE_BG			"loseBG"
#define LOSE_TITLE		"loseTitle"

//SOUND
#define LOGO_SFX			100

#define WELCOME_BGM			200

#define PLAY_BGM			300

#define WIN_BGM				400
#define LOSE_BGM			401

#define SHOP_BGM			500

#define INSTRUCTION_BGM		600

#define CREDIT_BGM			700

#define BUTTON_SFX			900
#define COIN				901
#define PEWPEW				902
#define REGEN				903
#define HIT					904
#define BOMB				905
#define WHOOSH				906
#define DEATH_SFX			907
#define TELEPORT_SFX		908
#define BUY_SUCCESS_SFX		909
#define BUY_FAIL_SFX		910


//SHOP ITEMS
#define ITEM_SELL							3
#define ITEM_COUNT							27
	//RESET BUTTON
#define ITEM_NAME_RESET						"Reset Items"
#define ITEM_DESCRIPTION_RESET				"Reset new items in the shop"
#define ITEM_PRICE_RESET					1
	//HEART_STONE
#define ITEM_HEART_STONE					1
#define BUTTON_ITEM_HEART_STONE				"buttonItemHeartStone"
#define ITEM_NAME_HEART_STONE				"Heart Stone"
#define ITEM_DESCRIPTION_HEART_STONE		"Increase 75 max HP"
#define ITEM_PRICE_HEART_STONE				1
	//MANA_CRYSTAL
#define ITEM_MANA_CRYSTAL					2
#define BUTTON_ITEM_MANA_CRYSTAL			"buttonItemManaCrystal"
#define ITEM_NAME_MANA_CRYSTAL				"Mana Crystal"
#define ITEM_DESCRIPTION_MANA_CRYSTAL		"Increase 75 max MP"
#define ITEM_PRICE_MANA_CRYSTAL				1
	//HERCULES_FIST
#define ITEM_HERCULES_FIST					3
#define BUTTON_ITEM_HERCULES_FIST			"buttonItemHerculesFist"
#define ITEM_NAME_HERCULES_FIST				"Hercules Fist"
#define ITEM_DESCRIPTION_HERCULES_FIST		"Increase 3 ATK"
#define ITEM_PRICE_HERCULES_FIST			1
	//ATHENA_SHIELD
#define ITEM_ATHENA_SHIELD					4
#define BUTTON_ITEM_ATHENA_SHIELD			"buttonItemAthenaShield"
#define ITEM_NAME_ATHENA_SHIELD				"Athena Shield"
#define ITEM_DESCRIPTION_ATHENA_SHIELD		"Increase 3 DEF"
#define ITEM_PRICE_ATHENA_SHIELD			1
	//CODEX_GIGAS
#define ITEM_CODEX_GIGAS					5
#define BUTTON_ITEM_CODEX_GIGAS				"buttonItemCodexGigas"
#define ITEM_NAME_CODEX_GIGAS				"Codex Gigas"
#define ITEM_DESCRIPTION_CODEX_GIGAS		"Increase 10% max MP & decrease 30% max HP"
#define ITEM_PRICE_CODEX_GIGAS				1
	//HERMES_SHOE
#define ITEM_HERMES_SHOE					6
#define BUTTON_ITEM_HERMES_SHOE				"buttonItemHermesShoe"
#define ITEM_NAME_HERMES_SHOE				"Hermes Shoe"
#define ITEM_DESCRIPTION_HERMES_SHOE		"Increase 3 SPEED"
#define ITEM_PRICE_HERMES_SHOE				1
	//TITAN_CHAIN
#define ITEM_TITAN_CHAIN					7
#define BUTTON_ITEM_TITAN_CHAIN				"buttonItemTitanChain"
#define ITEM_NAME_TITAN_CHAIN				"Titan Chain"
#define ITEM_DESCRIPTION_TITAN_CHAIN		"Increase 5 DEF & decrease 1 SPEED"
#define ITEM_PRICE_TITAN_CHAIN				1
	//ARES_BLADE
#define ITEM_ARES_BLADE						8
#define BUTTON_ITEM_ARES_BLADE				"buttonItemAresBlade"
#define ITEM_NAME_ARES_BLADE				"Ares Blade"
#define ITEM_DESCRIPTION_ARES_BLADE			"Increase 5 ATK & decrease 2 DEF"
#define ITEM_PRICE_ARES_BLADE				1
	//LIFE_STONE
#define ITEM_LIFE_STONE						9
#define BUTTON_ITEM_LIFE_STONE				"buttonItemLifeStone"
#define ITEM_NAME_LIFE_STONE				"Life Stone"
#define ITEM_DESCRIPTION_LIFE_STONE			"Increase 50 max HP & 1 DEF"
#define ITEM_PRICE_LIFE_STONE				1
	//OCEAN_SHARDS
#define ITEM_OCEAN_SHARDS					10
#define BUTTON_ITEM_OCEAN_SHARDS			"buttonItemOceanShards"
#define ITEM_NAME_OCEAN_SHARDS				"Ocean Shards"
#define ITEM_DESCRIPTION_OCEAN_SHARDS		"Increase 50 max MP & 1 DEF"
#define ITEM_PRICE_OCEAN_SHARDS				1
	//GIGANTIFICATION
#define ITEM_GIGANTIFICATION				11
#define BUTTON_ITEM_GIGANTIFICATION			"buttonItemGigantification"
#define ITEM_NAME_GIGANTIFICATION			"Gigantification"
#define ITEM_DESCRIPTION_GIGANTIFICATION	"Increase 4 ATK & decrease 1 SPPED"
#define ITEM_PRICE_GIGANTIFICATION			1
	//ARTEMIS_BLESSING
#define ITEM_ARTEMIS_BLESSING				12
#define BUTTON_ITEM_ARTEMIS_BLESSING		"buttonItemArtemisBlessing"
#define ITEM_NAME_ARTEMIS_BLESSING			"Artemis Blessing"
#define ITEM_DESCRIPTION_ARTEMIS_BLESSING	"Increase 25% max HP & 1 SPEED, decrease 40% max MP"
#define ITEM_PRICE_ARTEMIS_BLESSING			1
	//BARBATOS_FAVOR
#define ITEM_BARBATOS_FAVOR					13
#define BUTTON_ITEM_BARBATOS_FAVOR			"buttonItemBarbatosFavor"
#define ITEM_NAME_BARBATOS_FAVOR			"Barbatos Favor"
#define ITEM_DESCRIPTION_BARBATOS_FAVOR		"Increase 150 max HP & decrease 1 ATK"
#define ITEM_PRICE_BARBATOS_FAVOR			1
	//AAMON_CONTRACT
#define ITEM_AAMON_CONTRACT					14
#define BUTTON_ITEM_AAMON_CONTRACT			"buttonItemAamonContract"
#define ITEM_NAME_AAMON_CONTRACT			"Aamon Contract"
#define ITEM_DESCRIPTION_AAMON_CONTRACT		"Increase 150 max MP & decrease 1 ATK"
#define ITEM_PRICE_AAMON_CONTRACT			1
	//HEALTH_POTION
#define ITEM_HEALTH_POTION					15
#define BUTTON_ITEM_HEALTH_POTION			"buttonItemHealthPotion"
#define ITEM_NAME_HEALTH_POTION				"Health Potion"
#define ITEM_DESCRIPTION_HEALTH_POTION		"Heal 50% HP"
#define ITEM_PRICE_HEALTH_POTION			1
	//MANA_POTION
#define ITEM_MANA_POTION					16
#define BUTTON_ITEM_MANA_POTION				"buttonItemManaPotion"
#define ITEM_NAME_MANA_POTION				"Mana Potion"
#define ITEM_DESCRIPTION_MANA_POTION		"Heal 50% MP"
#define ITEM_PRICE_MANA_POTION				1
	//BLEEDING_FLOWER
#define ITEM_BLEEDING_FLOWER				17
#define BUTTON_ITEM_BLEEDING_FLOWER			"buttonItemBleedingFlower"
#define ITEM_NAME_BLEEDING_FLOWER			"Bleeding Flower"
#define ITEM_DESCRIPTION_BLEEDING_FLOWER	"Heal 100% HP & decrease 1 DEF"
#define ITEM_PRICE_BLEEDING_FLOWER			1
	//CORRUPTED_VINE
#define ITEM_CORRUPTED_VINE					18
#define BUTTON_ITEM_CORRUPTED_VINE			"buttonItemCorruptedVine"
#define ITEM_NAME_CORRUPTED_VINE			"Corrupted Vine"
#define ITEM_DESCRIPTION_CORRUPTED_VINE		"Heal 100% MP & decrease 1 DEF"
#define ITEM_PRICE_CORRUPTED_VINE			1
	//ROTTEN_GINSENG
#define ITEM_ROTTEN_GINSENG					19
#define BUTTON_ITEM_ROTTEN_GINSENG			"buttonItemRottenGinseng"
#define ITEM_NAME_ROTTEN_GINSENG			"Rotten Ginseng"
#define ITEM_DESCRIPTION_ROTTEN_GINSENG		"Heal 100% HP & decrease 1 SPEED"
#define ITEM_PRICE_ROTTEN_GINSENG			1
	//TWILIGHT_BERRY
#define ITEM_TWILIGHT_BERRY					20
#define BUTTON_ITEM_TWILIGHT_BERRY			"buttonItemTwilightBerry"
#define ITEM_NAME_TWILIGHT_BERRY			"Twilight Berry"
#define ITEM_DESCRIPTION_TWILIGHT_BERRY		"Heal 100% MP & decrease 1 SPEED"
#define ITEM_PRICE_TWILIGHT_BERRY			1
	//KEY
#define ITEM_KEY							21
#define BUTTON_ITEM_KEY						"buttonItemKey"
#define ITEM_NAME_KEY						"Key"
#define ITEM_DESCRIPTION_KEY				"Used for resetting new items in the shop"
#define ITEM_PRICE_KEY						1
	//FLAME_SWORD
#define ITEM_FLAME_SWORD					22
#define BUTTON_ITEM_FLAME_SWORD				"buttonItemFlameSword"
#define ITEM_NAME_FLAME_SWORD				"Flame Sword (Melee Skill)"
#define ITEM_DESCRIPTION_FLAME_SWORD		"..."
#define ITEM_PRICE_FLAME_SWORD				1
	//PYRO_WAVE
#define ITEM_PYRO_WAVE						23
#define BUTTON_ITEM_PYRO_WAVE				"buttonItemPyroWave"
#define ITEM_NAME_PYRO_WAVE					"PyroWave (Melee Skill)"
#define ITEM_DESCRIPTION_PYRO_WAVE			"..."
#define ITEM_PRICE_PYRO_WAVE				1
	//SOLAR_DESCEND
#define ITEM_SOLAR_DESCEND					24
#define BUTTON_ITEM_SOLAR_DESCEND			"buttonItemSolarDescend"
#define ITEM_NAME_SOLAR_DESCEND				"Solar Descend (Melee Skill)"
#define ITEM_DESCRIPTION_SOLAR_DESCEND		"..."
#define ITEM_PRICE_SOLAR_DESCEND			1
	//ICE_ARROW
#define ITEM_ICE_ARROW						25
#define BUTTON_ITEM_ICE_ARROW				"buttonItemIceArrow"
#define ITEM_NAME_ICE_ARROW					"Ice Arrow (Ranged Skill)"
#define ITEM_DESCRIPTION_ICE_ARROW			"..."
#define ITEM_PRICE_ICE_ARROW				1
	//GLACIAL_BLAST
#define ITEM_GLACIAL_BLAST					26
#define BUTTON_ITEM_GLACIAL_BLAST			"buttonItemGlacialBlast"
#define ITEM_NAME_GLACIAL_BLAST				"Glacial Blast (Ranged Skill)"
#define ITEM_DESCRIPTION_GLACIAL_BLAST		"..."
#define ITEM_PRICE_GLACIAL_BLAST			1
	//ABSOLUTE_ZERO
#define ITEM_ABSOLUTE_ZERO					27
#define BUTTON_ITEM_ABSOLUTE_ZERO			"buttonItemAbsoluteZero"
#define ITEM_NAME_ABSOLUTE_ZERO				"Absolute Zero (Ranged Skill)"
#define ITEM_DESCRIPTION_ABSOLUTE_ZERO		"..."
#define ITEM_PRICE_ABSOLUTE_ZERO			1