#include "Sound/AudioSystem.h"	

#include "Sound/Sound.h"
#include <SDL2/SDL_mixer.h>

namespace Core
{

	void AudioSystem::Init()
	{
		int initStatus = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		BJ_ASSERT(initStatus == 0, "Failed to init SDL_mixer! Mix_Error: % s", Mix_GetError());
		Mix_AllocateChannels(32); // Increase to 32 channels
	}

	void AudioSystem::Shutdown()
	{
		Mix_CloseAudio();
	}

	ActiveSound AudioSystem::PlaySound(SharedPtr<SoundBase> sound, float volumeMultiplier /*= 1.0f*/)
	{
		if (SharedPtr<SoundCue> sc = std::dynamic_pointer_cast<SoundCue>(sound))
		{
			float volume = s_SDLmaxVolume * s_MasterVolume * s_SFXVolume * sc->GetVolumeMultiplier() * volumeMultiplier;
			int32 channel = Mix_PlayChannel(-1, sc->Get(), !sc->IsOneShot());
			if (channel == -1)
			{
				BJ_LOG_ERROR("SDL_mixer error: %s", Mix_GetError());
				return ActiveSound {sc, -1};
			}
			Mix_Volume(channel, volume);
			ActiveSound as = { sc, channel };
			return as;
		}
		else
		{
			BJ_ASSERT(false, "Wrong sound type");
		}

	}

	void AudioSystem::PlayMusic(SharedPtr<SoundBase> sound, float volumeMultiplier /*= 1.0f*/)
	{
		if (SharedPtr<SoundMusic> sm = std::dynamic_pointer_cast<SoundMusic>(sound))
		{
			float volume = s_SDLmaxVolume * s_MasterVolume * s_MusicVolume * sm->GetVolumeMultiplier() * volumeMultiplier;
			Mix_VolumeMusic(volume);
			Mix_PlayMusic(sm->Get(), !sm->IsOneShot());
			s_CurrentMusic = sm;
		}
		else
		{
			BJ_ASSERT(false, "Wrong sound type");
		}
	}

	void AudioSystem::StopSound(ActiveSound sound)
	{
		Mix_HaltChannel(sound.Channel);
	}

	void AudioSystem::StopAllSounds()
	{
		Mix_HaltChannel(-1);
	}

	void AudioSystem::PauseMusic()
	{
		if (Mix_PlayingMusic())
		{
			Mix_PauseMusic();
		}
	}

	void AudioSystem::ResumeMusic()
	{
		if (Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
	}

	void AudioSystem::StopMusic()
	{
		Mix_HaltMusic();
	}

	void AudioSystem::SetMasterVolume(float volume)
	{
		float master = s_MasterVolume;
		s_MasterVolume = volume;
		RecalculateMusicVolume(volume, master);
		RecalculateSFXVolume(volume, master);
	}

	float AudioSystem::GetMasterVolume()
	{
		return s_MasterVolume;
	}

	void AudioSystem::SetMusicVolume(float volume)
	{
		float music = s_MusicVolume;
		s_MusicVolume = volume;
		RecalculateMusicVolume(volume, music);
	}

	float AudioSystem::GetMusicVolume()
	{
		return s_MusicVolume;
	}

	void AudioSystem::SetSFXVolume(float volume)
	{
		float sfx = s_SFXVolume;
		s_SFXVolume = volume;
		RecalculateSFXVolume(volume, sfx);
	}

	float AudioSystem::GetSFXVolume()
	{
		return s_SFXVolume;
	}

	void AudioSystem::RecalculateMusicVolume(float newVolume, float oldVolume)
	{
		if (s_CurrentMusic)
		{
			float currentMusicVolume = s_SDLmaxVolume * s_MasterVolume
				* s_MusicVolume * s_CurrentMusic->GetVolumeMultiplier() * s_CurrentMusic->GetActivetedVolume();

			Mix_VolumeMusic(newVolume * currentMusicVolume);
		}
		else
		{
			float currentMusicVolume = s_SDLmaxVolume * s_MasterVolume * s_MusicVolume;
			Mix_VolumeMusic(currentMusicVolume);
		}
	}

	void AudioSystem::RecalculateSFXVolume(float newVolume, float oldVolume)
	{
		float devider = 1;
		if (oldVolume == 0)
		{
			for (int i = 0; i < 32; i++)
			{
				Mix_Volume(i, s_SDLmaxVolume * s_MasterVolume * s_SFXVolume);
			}
		}
		else
		{
			for (int i = 0; i < 32; i++)
			{
				float channelVolume = Mix_Volume(i, -1) / oldVolume;
				Mix_Volume(i, newVolume * channelVolume);
			}
		}
	}
}