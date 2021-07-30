#pragma once
#include <vector>
#include <string>
#include <GLES2/gl2.h>
#include "Frame.h"

class Animation
{
public:
	std::string m_strResourceID;
	std::vector<Frame*> m_FrameList;

	Animation();
	Animation(std::string resourceID, const char* file);
	~Animation();

	void AddFrame(Frame *texture);
};