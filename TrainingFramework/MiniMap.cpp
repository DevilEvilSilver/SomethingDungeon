#include "stdafx.h"
#include "MiniMap.h"
#include "StatePlay.h"
#include "Room.h"
#include "MiniRoom.h"
#include "define.h"
MiniMap::MiniMap(Matrix translation, RoomType* mapType, Camera* camera) 
{
	m_Translation = translation;
	m_numRoomWeight = 32;
	m_numRoomHeight = 32;
	m_BoundWidget = new Widget("minimapBound", Vector2(0, 0), m_Translation);
	float fBoundWidth = m_BoundWidget->GetWorldMatrix(camera).m[0][0];
	float fBoundHeight = m_BoundWidget->GetWorldMatrix(camera).m[1][1];
	float fRoomWidth = fBoundWidth / m_numRoomWeight;
	float fRoomHeight = fBoundHeight / m_numRoomHeight;

	/*for (int i = 0; i < m_numRoomWeight; i++)
	{
		for (int j = 0; j < m_numRoomHeight; j++)
		{
			Matrix Translation;
			MiniRoom* Room;
			
			Translation.SetTranslation(m_BoundWidget->GetPosX() + i * fRoomWidth, m_BoundWidget->GetPosY() + j * fRoomHeight, 0);
			if (mapType[i * m_numRoomWeight + j]== WALL)
			{
				Room = new MiniRoom("minimapWall", Vector2(0, 0), Translation, Vector2(fRoomWidth, fRoomHeight));

			}
			else
			{
				Room = new MiniRoom("minimapRoom", Vector2(0, 0), Translation, Vector2(fRoomWidth, fRoomHeight));
			}
			m_RoomWidget.push_back(Room);
		}
	}*/
}

MiniMap::~MiniMap()
{
	delete m_BoundWidget;
	for (auto& obj : m_RoomWidget) {
		delete obj;
	}
}
void MiniMap::Update(float framTime)
{
	m_BoundWidget->Update(framTime);
	for (auto& obj : m_RoomWidget) {
		obj->Update(framTime);
	}
}
void MiniMap::Render(Camera* camera)
{
	m_BoundWidget->Render(camera);
	for (auto& obj : m_RoomWidget)
	{
		obj->Render(camera);
	}
}