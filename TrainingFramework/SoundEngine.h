#pragma once
#include "../Utilities/utilities.h"
#include<vector>
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

	void Init();
	
	int PlayOnly(int soundID);
	int PlayVolume(int soundID, float volume);
	int PlaySpeed(int soundID, float speed);
	int PlayInTSec(int soundID, int t);
	int PlayFirstTSec(int soundID, int t);
	int PlayLoop(int soundID);

	int Play(int soundID, float volume, float speed, bool isLoop);


};