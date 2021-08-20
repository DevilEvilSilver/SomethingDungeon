#include "stdafx.h"
#include "MiniRoom.h"
#include "Renderer.h"

MiniRoom::MiniRoom(std::string prefabID, Vector2 roomID, Matrix translationMatrix, Vector2 size)
	:Widget(prefabID, roomID,translationMatrix)
{
	ReSize(size);
}
MiniRoom::~MiniRoom()
{

}

//void MiniRoom::Render(Camera* camera)
//{
//	Renderer::GetInstance()->DrawAnimated(this, camera);
//}
//
//Matrix MiniRoom::GetWorldMatrix(Camera* camera)
//{
//	SetPosX(m_fCameraPosX + camera->GetPosition().x);
//	SetPosY(m_fCameraPosY + camera->GetPosition().y);
//	return m_WorldMatrix;
//}

void MiniRoom::ReSize(Vector2 size) 
{
	m_WorldMatrix.m[0][0] = size.x;
	m_WorldMatrix.m[1][1] = size.y;
}
