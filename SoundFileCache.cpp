// Cache class, might need a generic common cache for a larger projects.
// Might make sense to unload objects over time as well, pre-caching might
// also be nice.

#include "stdafx.h"
#include "SoundFileCache.h"

std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;

// No reason to have this
SoundFileCache::SoundFileCache(void) {}

// Functor, need to specify type in each call
SoundFileCache::~SoundFileCache(void) 
{
	std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer*>());
	std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music*>());
}

sf::Sound SoundFileCache::GetSound(std::string soundName) const
{
	// Check if already loaded
	std::map<std::string, sf::SoundBuffer *>::iterator itr = _sounds.find(soundName);

	if(itr == _sounds.end())
	{
		sf::SoundBuffer *soundBuffer = new sf::SoundBuffer();

		if(!soundBuffer->loadFromFile(soundName))
		{
			delete soundBuffer;
			throw SoundNotFoundExeception(soundName + " was not found in call to SoundFileCache::GetSound");
		}

		std::map<std::string, sf::SoundBuffer *>::iterator res = 
			_sounds.insert(std::pair<std::string, sf::SoundBuffer*>(soundName, soundBuffer)).first;

		sf::Sound sound;
		sound.setBuffer(*soundBuffer);

		return sound; // Copy, but ok due to it being relatively light
	}
	else
	{
		sf::Sound sound;
		sound.setBuffer(*itr->second);

		return sound;
	}

	throw SoundNotFoundExeception(soundName + " was not found in call to SoundFileCache::GetSound");
}

sf::Music* SoundFileCache::GetSong(std::string soundName) const
{
	std::map<std::string, sf::Music *>::iterator itr = _music.find(soundName);

	if(itr == _music.end())
	{
		sf::Music * song = new sf::Music();

		if(!song->openFromFile(soundName))
		{
			delete song;
			throw SoundNotFoundExeception(soundName + " was not found in call to SoundFileCache::GetSong");
		}
		else
		{
			std::map<std::string,sf::Music *>::iterator res = 
				_music.insert(std::pair<std::string,sf::Music*>(soundName,song)).first;

			return res->second; // Return pointer since we don't use cache
		}
	}
	else
	{
		return itr->second;
	}

	throw SoundNotFoundExeception(
		soundName + " was not found in call to SoundFileCache::GetSong");
}
