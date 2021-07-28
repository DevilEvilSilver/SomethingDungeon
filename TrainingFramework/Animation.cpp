#include <stdafx.h>
#include "Animation.h"

Animation::Animation() {

}

Animation::Animation(std::string resourceID, const char* file) {
	
}

Animation::~Animation() {
	for (auto& object : m_FrameList) {
		delete object;
	}
	m_FrameList.resize(0);
}

void Animation::AddFrame(Texture *texture) {
	m_FrameList.push_back(texture);
}