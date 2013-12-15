// Handles sounds.

#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"
#include "SoundFileCache.h"

class SoundProvider: public IAudioProvider
{
public:
	SoundProvider();

	void PlaySound(std::string filename);
	void PlaySong(std::string filename, bool looping = false);
	void StopAllSounds();

	bool IsSoundPlaying();
	bool IsSongPlaying();

private:
	// To be able to store multiple songs
	static const int MAX_SOUND_CHANNELS = 5;

	SoundFileCache _soundFileCache;
	sf::Sound   _currentSounds[MAX_SOUND_CHANNELS];
	std::string _currentSongName;
};
