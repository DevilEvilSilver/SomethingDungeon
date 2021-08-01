#pragma once
#include "../Utilities/utilities.h"
#include"Sound.h"
#include"SoundInstance.h"
#include<vector>
#include "Singleton.h"

class SoundEngine : public CSingleton<SoundEngine>
{
private:
	std::vector<Sound*> listSound;
	std::vector<SoundInstance*> listSI;

public:
	int soundID;
	SoLoud::Wav wav;
	

	SoundEngine();
	//SoundEngine(int soundID, const char* file);
	~SoundEngine();

	void Init();
	void AddSoundInstance(SoundInstance* si);


	std::vector<Sound*> getListSound();
	std::vector<SoundInstance*> getListSI();

	Sound* getSoundById(int id);
};