#include "stdafx.h"
#include "PhysicEngine.h"
#include "SceneManager.h"


PhysicEngine::PhysicEngine()
{
}


PhysicEngine::~PhysicEngine()
{
}
bool PhysicEngine::GetCollisSts(int i, int j)
{
	return m_collisStatus[i][j];
}
void PhysicEngine::UpdateCollision()
{/*
	std::vector<Object*> objectList = SceneManager::GetInstance()->m_ObjectList;
	for (int i = 0; i <objectList.size(); i++)
	{
		//Reset all collisArg before check collis
		

		for (int j = 0; j < objectList.size(); j++)
		{
			if (i != j)
			{
				CheckCollision(objectList.at(i), objectList.at(j));
			}
		}
	}
	*/
}
bool PhysicEngine::CheckCollision(Object* o1, Object* o2)
{
	if ((o1->m_iType == RECTANGLE && o2->m_iType == RECTANGLE) && CheckRectRectCollision(o1, o2))
	{
		return true;
	}
	else if ((o1->m_iType == RECTANGLE && o2->m_iType == RECTBOUND) && CheckRectBoundCollision(o1, o2))
	{
		return true;
	}
	else if ((o1->m_iType == RECTBOUND && o2->m_iType == RECTANGLE) && CheckRectBoundCollision(o2, o1))
	{
		return true;
	}
	else
		return false;
}
bool PhysicEngine::CheckRectCirCollision(Object* rect, Object* cir)
{
	return false;
}
bool PhysicEngine::CheckRectRectCollision(Object* rect1, Object* rect2)
{
	float *fr1 = rect1->GetHitBoxCurrentData();
	float *fr2 = rect2->GetHitBoxCurrentData();
	float fx1left = fr1[0];						float fx2left = fr2[0];
	float fy1down = fr1[1];						float fy2down = fr2[1];
	float fx1right = fr1[2];					float fx2right = fr2[2];
	float fy1top = fr1[3];						float fy2top = fr2[3];
	float fx1Center = (fx1left + fx1right) / 2;	float fx2Center = (fx2left + fx2right) / 2;
	float fy1Center = (fy1top + fy1down) / 2;	float fy2Center = (fy2top + fy2down) / 2;
	bool bSts = false;
	Vector3 R1(rect1->m_fWidth / 2, rect1->m_fHeight/2, 0);
	Vector3 R2(rect2->m_fWidth / 2, rect2->m_fHeight/2, 0);
	float fRectRectDistanceLimit = (R1 + R2).Length();
	Vector3 RectRectDistance(fx2Center - fx1Center, fy2Center - fy1Center, 0);
	float fRectRectDistance = RectRectDistance.Length();
	
	/*if (fRectRectDistance < fRectRectDistanceLimit)
	{
		std::cout << "PhysicEngine::CheckRectRectCollision\n";
		if (abs(fx1left - fx2right) < RECT_RECT_COLLISION_EPSILON)
		{
			rect1->SetCollisArg(LEFT_EDGE);
			rect2->SetCollisArg(RIGHT_EDGE);
			bSts = true;
		}
		else if (abs(fx1right - fx2left) < RECT_RECT_COLLISION_EPSILON)
		{
			rect1->SetCollisArg(RIGHT_EDGE);
			rect2->SetCollisArg(LEFT_EDGE);
			bSts = true;
		}
		else if (abs(fy1top - fy2down) < RECT_RECT_COLLISION_EPSILON)
		{
			rect1->SetCollisArg(TOP_EDGE);
			rect2->SetCollisArg(DOWN_EGDE);
			bSts = true;
		}
		else if (abs(fy1down - fy2top) < RECT_RECT_COLLISION_EPSILON)
		{
			rect1->SetCollisArg(DOWN_EGDE);
			rect2->SetCollisArg(TOP_EDGE);
			bSts = true;
		}
	}*/
	delete[] fr1;
	delete[] fr2;
	return bSts;
	
	float	x1 = rect1->GetPosX(),
		y1 = rect1->GetPosY(),
		w1 = rect1->m_fWidth,
		h1 = rect1->m_fHeight;

	float	x2 = rect2->GetPosX(),
		y2 = rect2->GetPosY(),
		w2 = rect2->m_fWidth,
		h2 = rect2->m_fHeight;

	if (x1 <= x2 + w2 &&
		x2 <= x1 + w1 &&
		y1 >= y2 - h2 &&
		y2 >= y1 - h1)
	{
		return true;
	}

	return false;
	
}
bool PhysicEngine::CheckCirCirCollision(Object* cir1, Object* cir2)
{
	float *c1 = cir1->GetHitBoxCurrentData();
	float *c2 = cir1->GetHitBoxCurrentData();
	float x1 = c1[0];		float x2 = c2[0];
	float y1 = c1[1];		float y2 = c2[1];
	float r1 = c1[4];		float r2 = c2[4];
	float delta = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	if (delta < (r1 + r2))
		return true;
	else
		return false;
}
bool PhysicEngine::CheckRectBoundCollision(Object* rect, Object* bound)
{
	bool bStsX = false;
	bool bStsY = false;
	float* data1 = rect->GetHitBoxCurrentData();
	float* data2 = bound->GetHitBoxCurrentData();

	float x11 = data1[0];		float x21 = data2[0];
	float y11 = data1[1];		float y21 = data2[1];
	float x12 = data1[2];		float x22 = data2[2];
	float y12 = data1[3];		float y22 = data2[3];

	if (abs(x11 - x21) < X_EPSILON || abs(x12 - x22) < X_EPSILON)
		bStsX = true;
	else
		bStsX = false;
	if (abs(y11 - y21) < Y_EPSILON || abs(y12 - x22) < Y_EPSILON)
		bStsY = true;
	else
		bStsY = false;
	delete[] data1;
	delete[] data2;
	if (bStsX || bStsY)
	{
		std::cout << "PhysicEngine::CheckRectBoundCollision\n";
	}
	return (bStsX || bStsY);
}
bool PhysicEngine::CheckCirBoundCollision(Object* rect, Object* bound)
{
	return false;
}
bool PhysicEngine::CheckMouseRectangle(Vector2 mousePos,Object* rect)
{
	float deltaX = mousePos.x - rect->GetPosX();
	float deltaY = rect->GetPosY() - mousePos.y;
	if (deltaX >= 0 && deltaY >= 0 && 
		deltaX <= rect->m_fWidth && 
		deltaY <= rect->m_fHeight)
		return true;

	return false;
}

bool PhysicEngine::GetCollumCollisStatus(int j)
{
	for (int i = 0; i < SceneManager::GetInstance()->m_ObjectList.size(); i++)
	{
		if (m_collisStatus[i][j] == true)
			return true;
	}
	return false;
}
