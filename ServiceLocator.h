// Master class to handle variouis services.
// Could be used for a number of services like renderer, IO, logger, etc.

#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"

class ServiceLocator
{
public:
	static IAudioProvider* GetAudio()  { return _audioProvider; } const

	static void RegisterServiceLocator(IAudioProvider *provider)
	{
		_audioProvider = provider;
	}

private:
	static IAudioProvider * _audioProvider;
};
