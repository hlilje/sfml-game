#pragma once

#include "audio_provider.hpp"
#include "sound_file_cache.hpp"


class SoundProvider: public AudioProvider {
private:
    static const unsigned int MAX_SOUND_CHANNELS = 5;

    SoundFileCache _sound_file_cache;
    sf::Sound      _current_sounds[MAX_SOUND_CHANNELS];
    std::string    _current_song_name;

public:
    SoundProvider();

    void PlaySound(const std::string & filename);
    void PlaySong(const std::string & filename, const bool looping = false);
    void StopAllSounds();

    bool IsSoundPlaying() const;
    bool IsSongPlaying() const;
};
