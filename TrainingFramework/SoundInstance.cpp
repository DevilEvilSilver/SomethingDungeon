#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "SoundInstance.h"
#include"SoundEngine.h"




SoundInstance::SoundInstance() {
}

SoundInstance::SoundInstance(int soundID) {
	this->m_isoundID = soundID;
	m_soloud.init();
}

SoundInstance::~SoundInstance() {}


void SoundInstance::PlayMusic( char *fileName, bool loop) {
	this->m_loop = loop;
	m_soloud.init();
	m_wav.load(fileName);
	m_ihandle = m_soloud.play(m_wav);
	m_soloud.setLooping(this->m_ihandle, m_loop);
	m_soloud.setVolume(m_ihandle, 5.0f);
}

void SoundInstance::PlayMusic(int soundId, bool isLoop) {
	this->m_loop = isLoop;

	Sound * sound = SoundEngine::GetInstance()->getSoundById(soundId);
	this->m_isoundID = soundId;
	
	m_ihandle = m_soloud.play(sound->m_wav);
	m_soloud.setLooping(this->m_ihandle, m_loop);
}

void SoundInstance::StopLoopMusic()
{
	this->PlayMusic(m_isoundID, false);
}

void SoundInstance::StopMusic(int soundId) {
	Sound* sound = SoundEngine::GetInstance()->getSoundById(soundId);
	this->m_soloud.stopAudioSource(sound->m_wav);
}

void SoundInstance::PlayClock(double numTime, int soundId, bool isLoop) {
	this->m_loop = isLoop;
	newtime = clock();
	if (newtime < (now + numTime)  ) {
		printf("stil in %d %d \t", now, newtime);
		this->PlayMusic(soundId,m_loop);
	}
	else {
		this->StopMusic(soundId);
	}

}






int SoundInstance::getHandleSound() {
	return this->m_ihandle;
}

SoLoud::Soloud SoundInstance::getSoloud() {
	return this->m_soloud;
}

void SoundInstance::setTimeNow(int now) {
	this->now = now;
}
