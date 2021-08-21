#pragma once
#include "vector"
#include "Camera.h"
#include "Widget.h"
#include "Room.h"
#include "Player.h"
class MiniMap
{
private:
    int m_numRoomWeight;
    int m_numRoomHeight;
    Matrix  m_Translation;
    Widget* m_MiniMapWidget;
    Widget* m_BoundWidget;
    Widget* m_PlayerWidget;
public:
    MiniMap(Matrix translation, RoomType* mapType, Camera* camera, Player* player);
    ~MiniMap();

    void Update(float framTime);
    void Render(Camera *camera);
};

