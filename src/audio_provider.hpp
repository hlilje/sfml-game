#pragma once


class AudioProvider {
public:
    virtual void PlaySound(const std::string & filename)                    = 0;
    virtual void PlaySong(const std::string & filename, const bool looping) = 0;
    virtual void StopAllSounds()                                            = 0;
    virtual bool IsSoundPlaying() const                                     = 0;
    virtual bool IsSongPlaying() const                                      = 0;
};
