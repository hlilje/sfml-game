#include "stdafx.hpp"
#include "sound_provider.hpp"


SoundProvider::SoundProvider():
    _current_song_name("") { }

void SoundProvider::PlaySound(const std::string & filename) {
    int avail_channel = -1;
    for (int i = 0; i < MAX_SOUND_CHANNELS; ++i) {
        if (_current_sounds[i].getStatus() != sf::Sound::Playing) {
            avail_channel = i;
            break;
        }
    }

    if (avail_channel != -1) {
        try {
            _current_sounds[avail_channel] = _sound_file_cache.GetSound(filename);
            _current_sounds[avail_channel].play();
        } catch (SoundNotFoundExeception & e) {
            // TODO: Handle error
        }
    }
}

void SoundProvider::PlaySong(const std::string & filename, const bool looping) {
    sf::Music * current_song;

    try {
        current_song = _sound_file_cache.GetSong(filename);
    } catch (SoundNotFoundExeception & e) {
        return;
    }

    if (_current_song_name != "") {
        try {
            sf::Music * prior_song = _sound_file_cache.GetSong(_current_song_name);
            if (prior_song->getStatus() != sf::Sound::Stopped)
                prior_song->stop();
        } catch (SoundNotFoundExeception & e) {
            // TODO: Handle error
        }
    }
    _current_song_name = filename;
    current_song->setLoop(looping);
    current_song->play();
}

void SoundProvider::StopAllSounds() {
    for (auto & sound : _current_sounds)
        sound.stop();

    if (_current_song_name != "") {
        sf::Music * const current_song = _sound_file_cache.GetSong(_current_song_name);
        if (current_song->getStatus() == sf::Sound::Playing)
            current_song->stop(); 
    }
}

bool SoundProvider::IsSoundPlaying() const {
    for (const auto & sound : _current_sounds) {
        if (sound.getStatus() == sf::Sound::Playing)
            return true;
    }
    return false;
}

bool SoundProvider::IsSongPlaying() const {
    if (_current_song_name != "")
        return _sound_file_cache.GetSong(_current_song_name)->getStatus() == sf::Music::Playing;  
    return false;
}
