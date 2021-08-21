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
	m_camera = camera;
	m_player = player;
	m_fCameraPosX = translation.m[3][0];
	m_fCameraPosY = translation.m[3][1];
	m_Translation = translation;
	m_numRoomWeight = 32;
	m_numRoomHeight = 32;
	m_MiniMapWidget = new Widget("minimap", Vector2(0, 0), m_Translation);
	//ReTexture
	Prefab* BoundPrefab = GetResource(m_MiniMapWidget->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);
	Animation* animation = GetResource(m_MiniMapWidget->m_strState, BoundPrefab->m_AnimationList);
	Frame* frame = animation->m_FrameList[0];
	frame->ReInitMiniMapFrame(mapType, Vector2(m_numRoomWeight,m_numRoomHeight));

	float fMiniMapWidth = m_MiniMapWidget->GetWorldMatrix(m_camera).m[0][0];
	float fMiniMapHeight = m_MiniMapWidget->GetWorldMatrix(m_camera).m[1][1];
	Vector2 playerPos(m_player->GetPosX() * fMiniMapWidth / (m_numRoomWeight * ROOM_WIDTH),
		m_player->GetPosY() * fMiniMapHeight / (m_numRoomHeight * ROOM_HEIGHT));
	playerPos.x = m_fCameraPosX + playerPos.x;
	playerPos.y = m_fCameraPosY - (fMiniMapHeight-playerPos.y);
	Matrix T;
	T.SetTranslation(playerPos.x, playerPos.y, 0);
	
	m_PlayerWidget = new Widget("minimapPlayer", Vector2(0, 0), T);
	m_BoundWidget = new Widget("minimapBound", Vector2(0, 0), m_Translation);
	
	
	
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
	m_PlayerWidget->Update(framTime);
	UpdatePlayerPos(framTime);
}
void MiniMap::Render(Camera* camera)
{
	//m_BoundWidget->Render(camera);
	
	m_MiniMapWidget->Render(camera);
	m_PlayerWidget->Render(camera);
	
}
void MiniMap::UpdatePlayerPos(float frameTime)
{
	float fMiniMapWidth = m_MiniMapWidget->GetWorldMatrix(m_camera).m[0][0];
	float fMiniMapHeight = m_MiniMapWidget->GetWorldMatrix(m_camera).m[1][1];
	Vector2 playerPos(m_player->GetPosX() * fMiniMapWidth / (m_numRoomWeight * ROOM_WIDTH),
		m_player->GetPosY() * fMiniMapHeight / (m_numRoomHeight * ROOM_HEIGHT));
	playerPos.x = m_fCameraPosX + playerPos.x;
	playerPos.y = m_fCameraPosY - (fMiniMapHeight - playerPos.y);
	m_PlayerWidget->m_fCameraPosX = playerPos.x;
	m_PlayerWidget->m_fCameraPosY = playerPos.y;
	
}