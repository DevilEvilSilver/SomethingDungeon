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
#define FILE_R_PLAY						"../Resources/States/R_PLAY.txt"
#define FILE_SD_PLAY					"../Resources/States/SD_PLAY.txt"
#define FILE_S_SHOP						"../Resources/States/S_SHOP.txt"
#define FILE_R_SHOP						"../Resources/States/R_SHOP.txt"
#define FILE_SD_SHOP					"../Resources/States/SD_SHOP.txt"
#define FILE_S_RESULT					"../Resources/States/S_RESULT.txt"
#define FILE_R_RESULT					"../Resources/States/R_RESULT.txt"
#define FILE_SD_RESULT					"../Resources/States/SD_RESULT.txt"

	//FILE RECORD
#define FILE_RECORD						"../Resources/record.txt"
#define FLOOR_1							"FLOOR_1"
#define FLOOR_2							"FLOOR_2"
#define FLOOR_3							"FLOOR_3"
#define FLOOR_BOSS						"FLOOR_BOSS"
#define RECORD_WIN						"WIN"
#define RECORD_LOSE						"LOSE"
#define INIT_PLAYER_HP					100
#define INIT_PLAYER_MP					100
#define INIT_PLAYER_ATK					5
#define INIT_PLAYER_DEF					5
#define INIT_PLAYER_GOLD				10000
#define INIT_PLAYER_KEY					100
#define INIT_PLAYER_SPEED				4.0f

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
#define AOE_SKILL		"aoeskill"

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

#define KEY				"key"
#define GOLD			"gold"
#define HP_PO			"hpPo"
#define MP_PO			"mpPo"
#define SPIKE_TRAP		"spikeTrap"
#define BOMB_TRAP		"bombTrap"

#define TREASURE		"treasure"
#define TOWER			"tower"

#define DOUBLE_BARRELS  "doubleBarrels"
#define TRIO_BARRELS	"trioBarrels"
#define BROKEN_WALL		"brokenWall"
#define POLE_1			"pole_1"
#define POLE_2			"pole_2"
#define POLE_3			"pole_3"
#define POLE_4			"pole_4"
//ENEMY
#define WITCH			"violetWitch"
#define B_ROBOTKNIGHT	"robotKnight"
#define SKELETON		"skeleton"
#define PLANT			"carnivorousPlant"
#define BEAR			"meleeSoldier"

#define CHEST			"chest"
#define ARROW_TOWER		"arrowTower"

#define MINIMAP_MAP		"minimap"
#define MINIMAP_PLAYER	"minimapPlayer"
#define MINIMAP_BOUND	"minimapBound"

//SKILL
#define	BULLET_SPEED	7

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

#define BUTTON_SFX			900
#define COIN				901
#define PEWPEW				902
#define REGEN				903
#define HIT					904
#define BOMB				905
#define WHOOSH				906
#define DEATH_SFX			907
#define TELEPORT_SFX		908


//SHOP ITEMS
#define ITEM_SELL							3
#define ITEM_COUNT							4
	//RESET BUTTON
#define ITEM_NAME_RESET						"Reset Items"
#define ITEM_DESCRIPTION_RESET				"Reset new items in the shop"
#define ITEM_PRICE_RESET					1
	//HEART_STONE
#define ITEM_HEART_STONE					1
#define BUTTON_ITEM_HEART_STONE				"buttonItemHeartStone"
#define ITEM_NAME_HEART_STONE				"Heart Stone"
#define ITEM_DESCRIPTION_HEART_STONE		"Increase 50 max HP"
#define ITEM_PRICE_HEART_STONE				1
	//MANA_CRYSTAL
#define ITEM_MANA_CRYSTAL					2
#define BUTTON_ITEM_MANA_CRYSTAL			"buttonItemManaCrystal"
#define ITEM_NAME_MANA_CRYSTAL				"Mana Crystal"
#define ITEM_DESCRIPTION_MANA_CRYSTAL		"Increase 50 max MP"
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
#define ITEM_DESCRIPTION_HERMES_SHOE		"Increase 5% SPEED"
#define ITEM_PRICE_HERMES_SHOE				1

	//LIFE_STONE
#define ITEM_LIFE_STONE						9
#define BUTTON_ITEM_LIFE_STONE				"buttonItemLifeStone"
#define ITEM_NAME_LIFE_STONE				"Life Stone"
#define ITEM_DESCRIPTION_LIFE_STONE			"Increase 50 max HP & 1 DEF"
#define ITEM_PRICE_LIFE_STONE				1

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