#include "stdafx.h"
#include "PhysicEngine.h"

PhysicEngine* PhysicEngine::s_Instance = NULL;
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
{
	std::vector<Object*> objectList = SceneManager::GetInstance()->m_ObjectList;
	for (int i = 0; i <objectList.size() ; i++)
	{
		for (int j = 0; j < objectList.size(); j++)
		{
			if (i != j)
			{
				CheckCollision(objectList.at(i), objectList.at(j));
				if (CheckCollision(objectList.at(i), objectList.at(j)))
				{

					m_collisStatus[i][j] = true;
					m_collisStatus[j][i] = true;
				}
				else
				{
					m_collisStatus[i][j] = false;
					m_collisStatus[j][i] = false;
				}
			}
		}
	}
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

	float *r1 = rect1->GetHitBoxData();
	float *r2 = rect2->GetHitBoxData();
	float x11 = r1[0];		float x21 = r2[0];
	float y11 = r1[1];		float y21 = r2[1];
	float x12 = r1[2];		float x22 = r2[2];
	float y12 = r1[3];		float y22 = r2[3];
	bool bSts = false;
	if (x11 <= x21 && x21 <= x12 && ((y11 <= y21 && y21 <= y12) || (y11 <= y22 && y22 <= y12)))
	{
		bSts = true;
	}
	else if (x11 <= x22 && x22 <= x12 && ((y11 <= y21 && y21 <= y12) || (y11 <= y22 && y22 <= y12)))
	{
		bSts = true;
	}
	else
		bSts = false;
	delete[] r1;
	delete[] r2;
	return bSts;
	
	/*
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
		y1 <= y2 + h2 &&
		y2 <= y1 + h1)
	{
		return true;
	}

	return false;
	*/
}
bool PhysicEngine::CheckCirCirCollision(Object* cir1, Object* cir2)
{
	float *c1 = cir1->GetHitBoxData();
	float *c2 = cir1->GetHitBoxData();
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
	float* data1 = rect->GetHitBoxData();
	float* data2 = bound->GetHitBoxData();

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
PhysicEngine* PhysicEngine::GetInstance()
{
	if (!s_Instance)
		s_Instance = new PhysicEngine();
	return s_Instance;
}

void PhysicEngine::ResetInstance() {
	delete s_Instance;
	s_Instance = NULL;
}