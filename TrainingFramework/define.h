#pragma once

#define SCREEN_W					960.0f
#define SCREEN_H					720.0f

#define FILE_SM						"../Resources/SM.txt"
#define FILE_RM						"../Resources/RM.txt"

#define PI							3.14159265f
#define HALFPI						(PI/2.0f)

#define TERRAIN_WRAP_SCALE			10
#define ROTATION_LOCK				85.0f

#define VERTEX_OFFSET_POS			0
#define VERTEX_OFFSET_NORM			(1 * sizeof(Vector3))
#define VERTEX_OFFSET_BINORM		(2 * sizeof(Vector3))
#define VERTEX_OFFSET_TGT			(3 * sizeof(Vector3))
#define VERTEX_OFFSET_UV			(4 * sizeof(Vector3))