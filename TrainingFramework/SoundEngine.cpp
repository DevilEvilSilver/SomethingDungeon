#pragma once
#include "stdafx.h"
#include "define.h"
#include "SoundEngine.h"

SoundEngine::SoundEngine() {
	Init();
	
}


SoundEngine::~SoundEngine() {
	//m_soloud.~Soloud();
	for (Sound* s : m_SoundList) {
		delete s;
	}
	m_SoundList.clear();

	m_soloud.deinit();
	
}

void SoundEngine::Init() 
{
	//READ FROM FILE
	FILE* fp;
	int soundNum, soundID;
	char filePath[40];
	Sound *sound;


	fp = fopen(FILE_SE, "r");
	if (fp == NULL) {
		printf("can not open file");
	}

	fscanf(fp, "SoundNum %d\n\n", &soundNum);
	for (int i = 0; i < soundNum; i++) {
		fscanf(fp, "#ID %d %s\n", &soundID, filePath );
		sound = new Sound(soundID, filePath);
		m_SoundList.push_back(sound);


	}

	printf("Done reading file Sound.txt\n");
	fclose(fp);


	//INIT SOLOUD
	m_soloud.init();
}

int SoundEngine::PlayOnly(int soundID)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);
			return handle;
			break;
		}
	}
	return NULL;
}
int SoundEngine::PlayVolume(int soundID, float volume)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);
			m_soloud.setVolume(handle,volume);
			return handle;
			break;
		}
	}
	return NULL;
}
int SoundEngine::PlaySpeed(int soundID, float speed)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);
			m_soloud.setRelativePlaySpeed(handle,speed);

			return handle;
			break;
		}
	}
	return NULL;
}
int SoundEngine::PlayInTSec(int soundID, int t)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);
			if (t != 0) {
				float speed = s->m_wav.getLength() / t;
				m_soloud.setRelativePlaySpeed(handle, speed);
			}


			return handle;
			break;
		}
	}
	return NULL;
}
int SoundEngine::PlayLoop(int soundID)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);
			m_soloud.setLooping(handle, true);

			return handle;
			break;
		}
	}
	return NULL;
}

int SoundEngine::PlayFirstTSec(int soundID, int t)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);
			m_soloud.scheduleStop(handle, t);

			return handle;
			break;
		}
	}
	return NULL;
}

int SoundEngine::Play(int soundID, float volume, float speed,bool isLoop)
{
	for (auto s : m_SoundList) {
		if (s->m_isoundID == soundID) {
			int handle = m_soloud.play(s->m_wav);

			m_soloud.setVolume(handle,volume);

			m_soloud.setRelativePlaySpeed(handle, speed);
			
			m_soloud.setLooping(handle,isLoop);



			return handle;
			break;
		}
	}
	return NULL;
}

void SoundEngine::Stop(int handle)
{
	m_soloud.stop(handle);
}

void SoundEngine::StopAll()
{
	m_soloud.stopAll();
}

void SoundEngine::SetPause(int handle, bool isPause)
{
	m_soloud.setPause(handle, isPause);
}

void SoundEngine::SetPauseAll(bool isPause)
{
	m_soloud.setPauseAll(isPause);
}

void SoundEngine::Fader(int handle, bool isFadeIn, float time)
{
	m_soloud.fadeVolume(handle, isFadeIn, time);
}

void SoundEngine::FaderAll(bool isFadeIn, float time)
{
	m_soloud.fadeGlobalVolume(isFadeIn, time);
}