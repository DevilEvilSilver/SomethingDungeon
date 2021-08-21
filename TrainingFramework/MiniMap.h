#pragma once
#include "vector"
#include "Camera.h"
#include "Widget.h"
#include "Room.h"
#include "Player.h"
class MiniMap
{
private:
    Camera* m_camera;
    float m_fCameraPosX, m_fCameraPosY;
    int m_numRoomWeight;
    int m_numRoomHeight;
    Player* m_player;
    Matrix  m_Translation;
    Widget* m_MiniMapWidget;
    Widget* m_BoundWidget;
    Widget* m_PlayerWidget;
public:
    MiniMap(Matrix translation, RoomType* mapType, Camera* camera, Player* player);
    ~MiniMap();

    void Update(float framTime);
    void UpdatePlayerPos(float frameTime);
    void Render(Camera *camera);
};

