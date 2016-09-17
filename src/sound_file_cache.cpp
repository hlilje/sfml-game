#include "stdafx.hpp"
#include "sound_file_cache.hpp"


std::map<std::string, sf::SoundBuffer *> SoundFileCache::_sounds;
std::map<std::string, sf::Music *> SoundFileCache::_music;


SoundFileCache::~SoundFileCache() {
    std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer *>());
    std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music *>());
}

sf::Sound SoundFileCache::GetSound(const std::string & sound_name) const {
    std::map<std::string, sf::SoundBuffer *>::iterator itr = _sounds.find(sound_name);

    if (itr == _sounds.end()) {
        sf::SoundBuffer * sound_buffer = new sf::SoundBuffer();

        if (!sound_buffer->loadFromFile(sound_name)) {
            delete sound_buffer;
            throw SoundNotFoundExeception(sound_name + " was not found in call to SoundFileCache::GetSound");
        }

        std::map<std::string, sf::SoundBuffer *>::iterator res = 
            _sounds.insert(std::pair<std::string, sf::SoundBuffer*>(sound_name, sound_buffer)).first;

        sf::Sound sound;
        sound.setBuffer(*sound_buffer);

        return sound;
    } else {
        sf::Sound sound;
        sound.setBuffer(*itr->second);

        return sound;
    }

    throw SoundNotFoundExeception(sound_name + " was not found in call to SoundFileCache::GetSound");
}

sf::Music * SoundFileCache::GetSong(const std::string & song_name) const {
    std::map<std::string, sf::Music *>::iterator itr = _music.find(song_name);

    if (itr == _music.end()) {
        sf::Music * const song = new sf::Music();

        if (!song->openFromFile(song_name)) {
            delete song;
            throw SoundNotFoundExeception(song_name + " was not found in call to SoundFileCache::GetSong");
        } else {
            std::map<std::string, sf::Music *>::iterator res = 
                _music.insert(std::pair<std::string,sf::Music*>(song_name,song)).first;

            return res->second;
        }
    } else {
        return itr->second;
    }

    throw SoundNotFoundExeception(song_name + " was not found in call to SoundFileCache::GetSong");
}
