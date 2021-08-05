#include "stdafx.h"
#include "Room.h"
#include "ResourceManager.h"
#include "Renderer.h"

Room::Room() {}

Room::Room(std::string prefabID, Matrix translationMatrix, RoomType roomType)
	: Object(prefabID, translationMatrix), m_RoomType(roomType) {

}

Room::~Room() {

}

void Room::Update(float frameTime) {
	m_fCurrFrameTime += frameTime;
}

void Room::Render(Camera* camera) {
	Renderer::GetInstance()->DrawAnimated(this, camera);
}