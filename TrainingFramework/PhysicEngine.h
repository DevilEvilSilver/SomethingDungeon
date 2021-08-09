#pragma once
#include "Object.h"
#include "math.h"
#include "define.h"
#include <iostream>
#include "Singleton.h"

class PhysicEngine:public Singleton<PhysicEngine>
{
private:
	
	bool m_collisStatus[10][10];   //ma tran trang thai va cham cua cac vat trong m_ObjectList, co the tang so luong neu can thiet
public:
	PhysicEngine();
	~PhysicEngine();
	void UpdateCollision();
	bool GetCollisSts(int i, int j);

	static bool CheckCollision(Object* o1, Object* o2);
	static bool CheckRectCirCollision(Object* rect, Object* cir);
	static bool CheckRectRectCollision(Object* rect1, Object* rect2);
	static bool CheckCirCirCollision(Object* cir1, Object* cir2);
	static bool CheckRectBoundCollision(Object* rect, Object* bound);
	static bool CheckCirBoundCollision(Object* rect, Object* bound);

	static bool CheckMouseRectangle(Vector2 mousePos,Object* rect);		//kiem tra click vao dau

	
};

