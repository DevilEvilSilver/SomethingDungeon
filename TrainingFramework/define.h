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
#define FILE_S_WELCOME					"../Resources/States/S_WELCOME.txt"
#define FILE_R_WELCOME					"../Resources/States/R_WELCOME.txt"
#define FILE_S_PLAY						"../Resources/States/S_PLAY.txt"
#define FILE_R_PLAY						"../Resources/States/R_PLAY.txt"
#define FILE_SE							"../Resources/Sound.txt"

//MAP
#define MAP_MAX_TUNNEL				160
#define TUNNEL_MAX_LENGTH			7
#define ROOM_WIDTH					20
#define ROOM_HEIGHT					20
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
#define PLAYER			"mainChar"
#define ENEMY			"enemy"
#define NORMAL_ROOM		"normalRoom"
#define WALL_ROOM		"wallRoom"
#define HOLE_ROOM		"holeRoom"

//ANIMATION
#define INIT_ANIM		"init"
	//CHARACTER
#define IDLE_LEFT		"idleLeft"
	//BUTTON
#define B_NORMAL			"normal"
#define B_PRESSED			"pressed"
#define B_HOVER				"hover"
#define B_UNAVAILABLE		"unavailable"
