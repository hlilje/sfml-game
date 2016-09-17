#pragma once


class SoundFileCache {
private:
    static std::map<std::string, sf::SoundBuffer *> _sounds;
    static std::map<std::string, sf::Music *> _music;

    template <typename T>
    struct Deallocator{
        void operator()(const std::pair<const std::string &, T > & p) {
            delete p.second;
        }
    };

public:
    ~SoundFileCache();

    sf::Sound GetSound(const std::string & sound_name) const;
    sf::Music * GetSong(const std::string & song_name) const;
};

class SoundNotFoundExeception : public std::runtime_error {
public:
    SoundNotFoundExeception(const std::string & message):
        std::runtime_error(message) { }
};
