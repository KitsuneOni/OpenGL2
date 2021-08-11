// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2021 Media Design School
//
// File Name   : AudioManager.h
// Description : A Class to handle the FMOD Audio System
// Author      : Neel Kolhe
// Mail        : Neel.Kolhe@mds.ac.nz
#pragma once
#include <fmod.hpp>
#include <iostream>

class AudioManager
{
public:
	// Create the Audio Manager
	AudioManager();
	// Set the New Audio Source
	void setAudio(const char* AudioSource, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* info, FMOD::Sound** sound);
	// Play the Sound
	void PlaySound(FMOD::Sound* Sound);

	// Initialize the Audio System
	bool AudioInit();
	// Update the Audio
	void Update();
	// Safely Shutdown
	void ShutDown();

	FMOD::Sound* BackgroundTrack;
	FMOD::Sound* FX_One;
	FMOD::Sound* FX_Two;
private: 
	FMOD::System* AudioSystem;


};

