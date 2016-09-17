#pragma once

#include "audio_provider.hpp"


class ServiceLocator {
private:
    static AudioProvider * _audio_provider;

public:
    static AudioProvider * GetAudio() {
        return _audio_provider;
    }

    static void RegisterServiceLocator(AudioProvider * const provider) {
        _audio_provider = provider;
    }
};
