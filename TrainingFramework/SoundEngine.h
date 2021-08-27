#pragma once
#include "../Utilities/utilities.h"
#include<vector>
#include <string>
#include "Singleton.h"
#include "Sound.h"

class SoundEngine : public Singleton<SoundEngine>
{
private:
	
public:
	SoLoud::Soloud m_soloud;
	std::vector<Sound*> m_SoundList;


	SoundEngine();
	~SoundEngine();

	void Init(std::string soundFile);
	
	int PlayOnly(int soundID);
	int PlayVolume(int soundID, float volume);
	int PlaySpeed(int soundID, float speed);
	int PlayInTSec(int soundID, int t);
	int PlayFirstTSec(int soundID, int t);
	int PlayLoop(int soundID);

	void Stop(int handle);
	void StopAll();
	void SetPause(int handle, bool isPause);
	void SetPauseAll(bool isPause);
	void Fader(int handle, bool isFadeIn, float time);
	void FaderAll(bool isFadeIn, float time);			//Only use when quitting game

	int Play(int soundID, float volume, float speed, bool isLoop);


};