#pragma once

//SYSTEM
#define SCREEN_W					960.0f
#define SCREEN_H					720.0f

#define PI							3.14159265f
#define HALFPI						(PI/2.0f)

#define ROTATION_LOCK				85.0f

#define VERTEX_OFFSET_POS			0
#define VERTEX_OFFSET_NORM			(1 * sizeof(Vector3))
#define VERTEX_OFFSET_BINORM		(2 * sizeof(Vector3))
#define VERTEX_OFFSET_TGT			(3 * sizeof(Vector3))
#define VERTEX_OFFSET_UV			(4 * sizeof(Vector3))

//INIT STATE
#define FILE_SM						"../Resources/SM.txt"
#define FILE_RM						"../Resources/RM.txt"
#define FILE_SE						"../Resources/Sound.txt"

//OBJECT
#define RECTANGLE					0
#define CIRCLE						1


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

//OBJECT
#define RECTANGLE					0
#define CIRCLE						1
#define RECTBOUND					2

//PHYSIC ENGINE
#define Y_EPSILON			0.5
#define X_EPSILON			0.1

#define LIMIT_FPS			30