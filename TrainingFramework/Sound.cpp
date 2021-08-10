#pragma once
#include "stdafx.h"
#include "Sound.h"





Sound::Sound(int soundID, const char* file) {
	m_isoundID = soundID;
	m_wav.load(file);


}

