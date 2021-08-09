#pragma once
#include <vector>
//#include "../Utilities/Math.h"
#include "../Utilities/utilities.h" 
#include<ctime>

class SoundInstance
{
	private:
		int m_isoundID;
		int m_ihandle;
		SoLoud::Wav m_wav;
		SoLoud::Soloud m_soloud;
		bool m_loop;
		int now;
		int newtime ;
		//SoundEngine soundEngine;
public:
	
	SoundInstance();
	SoundInstance(int soundID);
	~SoundInstance();

	void PlayMusic(char * fileName,bool isLoop);
	void PlayMusic(int soundId, bool isLoop);
	void StopLoopMusic();
	void PlayClock( double numTime, int soundId, bool isLoop);
	void StopMusic(int soundId);

	int getHandleSound();
	SoLoud::Soloud getSoloud();

	void setTimeNow(int now);
};