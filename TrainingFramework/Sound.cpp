#pragma once
#include "stdafx.h"
#include "Sound.h"


Sound::Sound() 
{
}

Sound::~Sound() 
{
}

Sound::Sound(int soundID, const char* file) {
	this->m_isoundID = soundID;
	this->m_wav.load(file);
}