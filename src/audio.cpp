#include "audio.h"

Audio::Audio()
:sounds_(static_cast<int>(Audio::Sound::kSoundMax)),
music_(NULL)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Couldn't initialize SDL Mixer\n");
		exit(1);
	}

	Mix_AllocateChannels(8);

    InitSounds();
}

Audio::~Audio()
{
    sounds_.erase(sounds_.begin(), sounds_.end());
    if (music_ != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music_);
		music_ = NULL;
	}
}

void Audio::LoadSounds()
{
	sounds_[static_cast<int>(Audio::Sound::kSoundPlayerFire)] = Mix_LoadWAV("../sound/334227__jradcoolness__laser.ogg");
	sounds_[static_cast<int>(Audio::Sound::kSoundEnemyFire)] = Mix_LoadWAV("../sound/196914__dpoggioli__laser-gun.ogg");
	sounds_[static_cast<int>(Audio::Sound::kSoundPlayerDie)] = Mix_LoadWAV("../sound/245372__quaker540__hq-explosion.ogg");
	sounds_[static_cast<int>(Audio::Sound::kSoundEnemyDie)] = Mix_LoadWAV("../sound/10 Guage Shotgun-SoundBible.com-74120584.ogg");
}

void Audio::InitSounds()
{	
	LoadSounds();
    LoadMusic("../music/Mercury.ogg");
}

void Audio::LoadMusic(const std::string& filename)
{
	if (music_ != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music_);
		music_ = NULL;
	}

	music_ = Mix_LoadMUS(filename.c_str());
}

void Audio::PlayMusic(int loop) const
{
	Mix_PlayMusic(music_, (loop) ? -1 : 0);
}

void Audio::PlaySound(Sound sound_id, Channel channel) const
{
	Mix_PlayChannel(static_cast<int>(channel), sounds_[static_cast<int>(sound_id)], 0);
}