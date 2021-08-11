#include "AudioManager.h"

AudioManager::AudioManager()
{
	AudioInit();
}

void AudioManager::setAudio(const char* AudioSource, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* info, FMOD::Sound** sound)
{
	if (AudioSystem->createSound(AudioSource, mode, info, sound) != FMOD_OK)
	{
		std::cout << "FMOD ERROR: Loading sound using create sound (" << AudioSource << ", " << mode << ", " << info  << ")." << std::endl;
	}
}

void AudioManager::PlaySound(FMOD::Sound* Sound)
{
	AudioSystem->playSound(Sound, 0, false, 0);
}


bool AudioManager::AudioInit()
{
	if (FMOD::System_Create(&AudioSystem) != FMOD_OK)
	{
		std::cout << "FMOD ERROR: Audio System Failed to Create." << std::endl;
		return false;
	}
	if (AudioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0) != FMOD_OK)
	{
		std::cout << "FMOD ERROR: Audio System Failed to Initialize." << std::endl;
		return false;
	}
	return true;
}

void AudioManager::Update()
{
	AudioSystem->update();
}

void AudioManager::ShutDown()
{
	FX_Two->release();
	FX_One->release();
	BackgroundTrack->release();
	AudioSystem->release();
}
