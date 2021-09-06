#include "stdafx.h"
#include "CollisionManager.h"
#include "define.h"

CollisionManager::CollisionManager()
{

}
CollisionManager::~CollisionManager()
{

}
void CollisionManager::UpdateCollision(float frameTime)
{
	std::vector<Object*> objectList = StatePlay::GetInstance()->m_ObjectList;
	for (int i = 0; i < objectList.size(); i++)
	{
		for (int j = 0; j < objectList.size(); j++)
		{
			if (i < j)
			{
				CheckCollision(objectList.at(i), objectList.at(j), frameTime);
			}
		}
	}
}
bool CollisionManager::CheckCollision(Object* o1, Object* o2, float frameTime)
{
	if (o2!=nullptr)
	if ((o1->m_iType == RECTANGLE && o2->m_iType == RECTANGLE) && CheckRectRectCollision(o1, o2, frameTime))
	{
		return true;
	}
	
	return false;
}
bool CollisionManager::CheckRectRectCollision(Object* dynamicObj, Object* staticObj, float frameTime)
{
	
	bool status = false;
	float* fCurrent = dynamicObj->GetHitBoxCurrentData();
	float x1Current = fCurrent[0];
	float y1Current = fCurrent[1];
	float v1x = fCurrent[4];
	float v1y = fCurrent[5];
	float	x1 = x1Current + v1x * frameTime,
		y1 = y1Current + v1y * frameTime,
		w1 = dynamicObj->m_fWidth,
		h1 = dynamicObj->m_fHeight;

	float* fCurrent2 = staticObj->GetHitBoxCurrentData();//new

	float	x2 = fCurrent2[0],//staticObj->GetPosX(),
		y2 = fCurrent2[1],//staticObj->GetPosY(),
		w2 = staticObj->m_fWidth,
		h2 = staticObj->m_fHeight;

	if (x1 <= x2 + w2 &&
		x2 <= x1 + w1 &&
		y1 >= y2 - h2 &&
		y2 >= y1 - h1)
	{
		status = true;
	}
	if (status && frameTime)
	{
		float dx = 0, dy = 0;
		Vector2 C1(x1Current + w1 / 2.0f, y1Current - h1 / 2.0f);
		Vector2 C2(x2 + w2 / 2.0f, y2 - h2 / 2.0f);
		Vector2 tempDis(x1 - x1Current, y1 - y1Current);
		Vector2 tempC1 = C1 + tempDis;
		Vector2 tempDisC1C2 = tempC1 - C2;
		int i = 0;
		while (1)
		{
			i++;
			tempDis = tempDis * 0.9f;
			tempC1 = C1 + tempDis;
			tempDisC1C2 = tempC1 - C2;
			if ((abs(tempDisC1C2.x) > ((w1 + w2) / 2) || abs(tempDisC1C2.y) > ((h1 + h2) / 2)))
				break;
			if (i == 30)
			{
				tempDis.x = v1x * frameTime;
				tempDis.y = v1y * frameTime;
				if (abs(C1.x - C2.x) <= ((w1 + w2) / 2)) {
					tempDis.y = 0.0f;
				}
				if (abs(C1.y - C2.y) <= ((h1 + h2) / 2)) {
					tempDis.x = 0.0f;
				}

				break;
			}
		}
		if (frameTime)
		{
			dx = tempDis.x;
			dy = tempDis.y;
			dynamicObj->SetVelocityX(dx / frameTime);
			dynamicObj->SetVelocityY(dy / frameTime);
		}
	}
	delete[] fCurrent;
	delete[] fCurrent2;

	return status;
}

bool CollisionManager::CheckRectRectCollision2(Object* dynamicObj, Object* staticObj, float frameTime)
{
	bool status = false;
	float* fCurrent = dynamicObj->GetHitBoxCurrentData();
	float x1Current = fCurrent[0];
	float y1Current = fCurrent[1];
	float v1x = fCurrent[4];
	float v1y = fCurrent[5];
	float	x1 = x1Current + v1x * frameTime,
		y1 = y1Current + v1y * frameTime,
		w1 = dynamicObj->m_fWidth,
		h1 = dynamicObj->m_fHeight;

	float* fCurrent2 = staticObj->GetHitBoxCurrentData();//new

	float	x2 = fCurrent2[0],//staticObj->GetPosX(),
		y2 = fCurrent2[1],//staticObj->GetPosY(),
		w2 = staticObj->m_fWidth,
		h2 = staticObj->m_fHeight;

	if (x1 <= x2 + w2 &&
		x2 <= x1 + w1 &&
		y1 >= y2 - h2 &&
		y2 >= y1 - h1)
	{
		status = true;
	}
	if (status && frameTime)
	{
		float dx = 0, dy = 0;
		Vector2 C1(x1Current + w1 / 2.0f, y1Current - h1 / 2.0f);
		Vector2 C2(x2 + w2 / 2.0f, y2 - h2 / 2.0f);
		Vector2 tempDis(x1 - x1Current, y1 - y1Current);
		Vector2 tempC1 = C1 + tempDis;
		Vector2 tempDisC1C2 = tempC1 - C2;
		int i = 0;
		while (1)
		{
			i++;
			tempDis = tempDis * 0.9f;
			tempC1 = C1 + tempDis;
			tempDisC1C2 = tempC1 - C2;

			x1 = tempC1.x - w1 / 2.0f;
			x2 = C2.x - w2 / 2.0f;
			y1 = tempC1.y + h1 / 2.0f;
			y2 = C2.y + h2 / 2.0f;
			if (x1 <= x2 + w2 &&
				x2 <= x1 + w1 &&
				y1 >= y2 - h2 &&
				y2 >= y1 - h1)
			{
				status = true;
			}
			else break;
			if (i == 30)
			{
				/*tempDis.x = v1x * frameTime;
				tempDis.y = v1y * frameTime;*/
				//if (abs(C1.x - C2.x) <= ((w1 + w2) / 2)) {
				tempDis.y = 0.0f;
				//}
				//if (abs(C1.y - C2.y) <= ((h1 + h2) / 2)) {
				tempDis.x = 0.0f;
				//}
				break;
			}
		}
		if (frameTime)
		{
			dx = tempDis.x;
			dy = tempDis.y;
			dynamicObj->SetVelocityX(dx / frameTime);
			dynamicObj->SetVelocityY(dy / frameTime);
		}
	}
	delete[] fCurrent;
	delete[] fCurrent2;

	return status;
}
