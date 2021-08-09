#pragma once
#include "../Utilities/utilities.h"


class Sound
{
public:
	int m_isoundID;
	SoLoud::Wav m_wav;

	Sound(int soundID, const char* file);


};