// General audio provider master class.

#pragma once

#include "stdafx.h"

// Purely virtual
class IAudioProvider
{
public:
	// No virtual constructor since it may not be called
	virtual void PlaySound(std::string filename) = 0; // Makes them purely virtual
	virtual void PlaySong(std::string filename, bool looping) = 0;
	virtual void StopAllSounds() = 0;

	virtual bool IsSoundPlaying() = 0;
	virtual bool IsSongPlaying() = 0;
};
