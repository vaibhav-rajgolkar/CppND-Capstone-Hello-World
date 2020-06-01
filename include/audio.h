#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <vector>
#include "SDL2/SDL_mixer.h"


class Audio
{
public:
    enum class Channel
    {
	kChannleAny = -1,
	kChannelPlayer,
	kChannelEnemy
    };

    enum class Sound
    {
    kSoundPlayerFire,
    kSoundEnemyFire,
    kSoundPlayerDie,
    kSoundEnemyDie,
    kSoundMax
    };

    Audio();
    ~Audio();

    // Disable copy and assignment of class
    Audio(const Audio& source) = delete;
    Audio& operator=(const Audio& source) = delete;


void PlayMusic(int loop) const;
void PlaySound(Sound sound_id, Channel channel) const;

private:
std::vector<Mix_Chunk*> sounds_;
Mix_Music *music_;

void InitSounds();
void LoadSounds();
void LoadMusic(const std::string& filename);

};

#endif //AUDIO_H