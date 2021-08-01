#pragma once
#include "stdafx.h"
#include "SoundEngine.h"

SoundEngine::SoundEngine() {
}

SoundEngine::~SoundEngine() {
}

void SoundEngine::Init() 
{
	FILE* fp;
	int soundNum, soundID;
	char filePath[40];
	Sound *sound;
	SoundInstance* si;

	fp = fopen("../Resources/Sound.txt", "r");
	if (fp == NULL) {
		printf("can not open file");
	}

	fscanf(fp, "SoundNum %d\n\n", &soundNum);
	for (int i = 0; i < soundNum; i++) {
		fscanf(fp, "#ID %d %s\n", &soundID, filePath );
		sound = new Sound(soundID, filePath);
		listSound.push_back(sound);
		si = new SoundInstance(soundID);
		listSI.push_back(si);
	}

	printf("Done reading file Sound.txt\n");
	fclose(fp);
}

void SoundEngine::AddSoundInstance(SoundInstance* si)
{
	listSI.push_back(si);
}


std::vector<Sound*> SoundEngine::getListSound() {
	return this->listSound;
}

std::vector<SoundInstance*> SoundEngine::getListSI() {
	return this->listSI;
}

Sound* SoundEngine::getSoundById(int id) {
	for (Sound* sound : listSound) {
		if (sound->m_isoundID == id) {
			printf("found out!!\n");
			return sound;
		}
	}
	printf("can not find out sound with Id = %d\n", id);
	return new Sound();
}