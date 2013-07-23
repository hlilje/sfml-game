// A cache for sounds.

#pragma once

#include "SFML/Audio.hpp"

class SoundFileCache
{
public:
	SoundFileCache(void);
	~SoundFileCache(void);

	sf::Sound GetSound(std::string) const; // Lightweight, copy it
	sf::Music* GetSong(std::string) const; // Heavy, send pointer

private:
	static std::map<std::string, sf::SoundBuffer*> _sounds;
	static std::map<std::string, sf::Music*> _music;

	// Not used, for demonstration
	/*struct SoundFileDeallocator
	{
		void operator()(const std::pair<std::string,sf::SoundBuffer*> & p) 
		{
			delete p.second;
		}
	};

	struct MusicFileDeallocator
	{
		void operator()(const std::pair<std::string,sf::Music*> & p) 
		{
			delete p.second;
		}
	};*/

	template <typename T> // Fundamental for modern C++ programming
	struct Deallocator{
		void operator()(const std::pair<std::string,T> &p) 
		{
			delete p.second;
		}
	};
};

// More for info than implementation
class SoundNotFoundExeception : public std::runtime_error
{
public:
	SoundNotFoundExeception(std::string const& msg):
		std::runtime_error(msg)
	{}
};
