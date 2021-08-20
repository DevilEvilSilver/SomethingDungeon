#pragma once
#include "vector"
#include "Camera.h"
#include "Widget.h"
#include "Room.h"
class MiniMap
{
private:
    int m_numRoomWeight;
    int m_numRoomHeight;
    Matrix  m_Translation;
    Widget* m_BoundWidget;
    std::vector<Widget*> m_RoomWidget;
public:
    MiniMap(Matrix translation, RoomType* mapType, Camera* camera);
    ~MiniMap();

    void Update(float framTime);
    void Render(Camera *camera);
};

