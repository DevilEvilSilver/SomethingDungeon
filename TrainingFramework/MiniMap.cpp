#include "stdafx.h"
#include "MiniMap.h"
#include "StatePlay.h"
#include "Room.h"
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
	m_playerPos.x = 0;
	m_playerPos.y = 0;
	m_camera = camera;
	m_player = player;
	m_fCameraPosX = translation.m[3][0];
	m_fCameraPosY = translation.m[3][1];
	m_Translation = translation;
	m_mapWidth = MAP_WIDTH;
	m_mapHeight = MAP_HEIGHT;
	m_MiniMapWidget = new Widget(MINIMAP_MAP, Vector2(0, 0), m_Translation);
	//Create Minimap Texture
	Prefab* miniMap = GetResource(m_MiniMapWidget->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);
	Animation* animation = GetResource(m_MiniMapWidget->m_strState, miniMap->m_AnimationList);
	Frame* frame = animation->m_FrameList[0];
	frame->ReInitMiniMapFrame(mapType, Vector2(m_mapWidth, m_mapHeight));

	m_PlayerWidget = new Widget(MINIMAP_PLAYER, Vector2(0, 0), translation);
	//init PlayerPos on Minimap
	/*float fMiniMapWidth = m_MiniMapWidget->GetWorldMatrix(m_camera).m[0][0];
	float fMiniMapHeight = m_MiniMapWidget->GetWorldMatrix(m_camera).m[1][1];
	Vector2 playerPos(m_player->GetPosX() * fMiniMapWidth / (m_mapWidth * ROOM_WIDTH),
						m_player->GetPosY() * fMiniMapHeight / (m_mapHeight * ROOM_HEIGHT));
	m_PlayerWidget->m_fCameraPosX = m_fCameraPosX + playerPos.x - m_PlayerWidget->GetWorldMatrix(m_camera).m[0][0]/2;
	m_PlayerWidget->m_fCameraPosY = m_fCameraPosY - (fMiniMapHeight - playerPos.y) + m_PlayerWidget->GetWorldMatrix(m_camera).m[1][1]/2;*/
	
	m_BoundWidget = new Widget(MINIMAP_BOUND, Vector2(0, 0), m_Translation);
	
	
	
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
	UpdatePlayerWidgetPos(framTime);
}
void MiniMap::Render(Camera* camera)
{
	m_MiniMapWidget->Render(camera,Vector2(m_PlayerWidget->GetPosX(),m_PlayerWidget->GetPosY()));
	m_PlayerWidget->Render(camera);
	m_BoundWidget->Render(camera);
}
void MiniMap::UpdatePlayerWidgetPos(float frameTime)
{
	float fMiniMapWidth = m_MiniMapWidget->GetWorldMatrix(m_camera).m[0][0];
	float fMiniMapHeight = m_MiniMapWidget->GetWorldMatrix(m_camera).m[1][1];
	Vector2 playerPos(m_player->GetPosX() * fMiniMapWidth / (m_mapWidth * ROOM_WIDTH),
		m_player->GetPosY() * fMiniMapHeight / (m_mapHeight * ROOM_HEIGHT));
	m_PlayerWidget->m_fCameraPosX = m_fCameraPosX + playerPos.x - m_PlayerWidget->GetWorldMatrix(m_camera).m[0][0] / 2;
	m_PlayerWidget->m_fCameraPosY = m_fCameraPosY - (fMiniMapHeight - playerPos.y) + m_PlayerWidget->GetWorldMatrix(m_camera).m[1][1] / 2;
	m_playerPos.x = playerPos.x;
	m_playerPos.y = fMiniMapHeight - playerPos.y;
}