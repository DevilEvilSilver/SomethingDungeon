#pragma once

//SYSTEM
#define SCREEN_W					1080.0f
#define SCREEN_H					720.0f

#define LIMIT_FPS					200

#define PI							3.14159265f
#define HALFPI						(PI/2.0f)

#define ROTATION_LOCK				85.0f

#define VERTEX_OFFSET_POS			0
#define VERTEX_OFFSET_NORM			(1 * sizeof(Vector3))
#define VERTEX_OFFSET_BINORM		(2 * sizeof(Vector3))
#define VERTEX_OFFSET_TGT			(3 * sizeof(Vector3))
#define VERTEX_OFFSET_UV			(4 * sizeof(Vector3))

//INIT STATE
#define FILE_S_LOAD						"../Resources/States/S_LOAD.txt"
#define FILE_R_LOAD						"../Resources/States/R_LOAD.txt"
#define FILE_S_LOGO						"../Resources/States/S_LOGO.txt"
#define FILE_R_LOGO						"../Resources/States/R_LOGO.txt"
#define FILE_S_WELCOME					"../Resources/States/S_WELCOME.txt"
#define FILE_R_WELCOME					"../Resources/States/R_WELCOME.txt"
#define FILE_S_PLAY						"../Resources/States/S_PLAY.txt"
#define FILE_R_PLAY						"../Resources/States/R_PLAY.txt"
#define FILE_SE							"../Resources/Sound.txt"

//MAP
#define MAP_MAX_TUNNEL				160
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

//PREFAB
#define TRANSISTION		"transition"
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

#define MINIMAP_MAP		"minimap"
#define MINIMAP_PLAYER	"minimapPlayer"
#define MINIMAP_BOUND	"minimapBound"

//SKILL
#define	BULLET_SPEED	7.0f

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
#define GOLD_SPIN		"goldspin"
#define HP_POTION		"hpPotion"
#define MP_POTION		"mpPotion"

	//TRAP
#define BOMB_INIT		"bombInit"
#define BOOMED			"boomed"
#define SPIKE			"spike"
#define CHEST			"chest"
#define ARROW_TOWER		"arrowTower"

//SOUND
#define WELCOME_BGM			0
#define LOGO_SFX			1
#define BUTTON_SFX			2

#define COIN				3
#define LOSE				4
#define PEWPEW				5
#define REGEN				6
#define WIN					7
#define HIT					8
#define BOMB				9
#define WHOOSH				10

//MAP
#define MAP_WIDTH			32
#define MAP_HEIGHT			32
