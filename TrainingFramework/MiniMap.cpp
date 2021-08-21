#include "stdafx.h"
#include "MiniMap.h"
#include "StatePlay.h"
#include "Room.h"
#include "MiniRoom.h"
#include "define.h"
#include "Prefab.h"
#include "Animation.h"
#include "Frame.h"
#include "ResourceManager.h"
template <class T>
T GetResource(std::string id, std::vector<T> objList) {
	for (auto& obj : objList) {
		if (!strcmp(id.c_str(), obj->m_strResourceID.c_str()))
			return obj;
	}
	return 0;
}
MiniMap::MiniMap(Matrix translation, RoomType* mapType, Camera* camera, Player* player)
{
	m_Translation = translation;
	m_numRoomWeight = 32;
	m_numRoomHeight = 32;
	m_MiniMapWidget = new Widget("minimap", Vector2(0, 0), m_Translation);
	float fBoundWidth = m_MiniMapWidget->GetWorldMatrix(camera).m[0][0];
	float fBoundHeight = m_MiniMapWidget->GetWorldMatrix(camera).m[1][1];
	//ReTexture
	Prefab* BoundPrefab = GetResource(m_MiniMapWidget->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);
	Animation* animation = GetResource(m_MiniMapWidget->m_strState, BoundPrefab->m_AnimationList);
	Frame* frame = animation->m_FrameList[0];
	frame->ReInitMiniMapFrame(mapType, Vector2(m_numRoomWeight,m_numRoomHeight));

	Vector2 playerPos(0, 0);
	m_BoundWidget = new Widget("minimapBound", Vector2(0, 0), m_Translation);
	m_PlayerWidget = new Widget("minimapPlayer", Vector2(0, 0), m_Translation);
	
	
}

MiniMap::~MiniMap()
{
	delete m_MiniMapWidget;
	delete m_BoundWidget;
	delete m_PlayerWidget;
}
void MiniMap::Update(float framTime)
{
	m_BoundWidget->Update(framTime);
	m_MiniMapWidget->Update(framTime);
	//m_PlayerWidget->Update(framTime);
}
void MiniMap::Render(Camera* camera)
{
	//m_BoundWidget->Render(camera);
	
	m_MiniMapWidget->Render(camera);
	m_PlayerWidget->Render(camera);
	
}