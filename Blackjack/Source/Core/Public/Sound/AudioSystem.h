#pragma once
#include "Core/CoreDefines.h"
#include "Sound/ActiveSound.h"

namespace Core
{
	class SoundBase;
	class SoundMusic;

	class AudioSystem
	{
	public:
		static void Init();
		static void Shutdown();

		static ActiveSound PlaySound(SharedPtr<SoundBase> sound, float volumeMultiplier = 1.0f);
		static void PlayMusic(SharedPtr<SoundBase> sound, float volumeMultiplier = 1.0f);
		static void StopSound(ActiveSound sound);
		static void StopAllSounds();
		static void PauseMusic();
		static void ResumeMusic();
		static void StopMusic();
		static bool IsMusicPlaying();
		static bool IsMusicPaused();
		static bool IsMusicMuted();
		static void MuteSound();
		static void UnmuteSound();
		static bool IsSoundMuted();

		/*
		* In range [0, 1]
		* Sound effect (or music) need to be restarted to take effect
		*/
		static void SetMasterVolume(float volume);
		static float GetMasterVolume();

		static void SetMusicVolume(float volume);
		static float GetMusicVolume();

		static void  SetSFXVolume(float volume);
		static float GetSFXVolume();

	private:
		static void RecalculateMusicVolume(float newVolume, float oldVolume);
		/** if oldVolume == 0, active sfx individual volumes will be ignored */
		static void RecalculateSFXVolume(float newVolume, float oldVolume);


	private:
		inline static SharedPtr<SoundMusic> s_CurrentMusic;

		inline static float s_MusicVolume = 1.0f;
		inline static float s_SFXVolume = 1.0f;

		inline static float s_MasterVolume = 1.0f;
		inline static float s_SDLmaxVolume = 128.0f;

		inline static bool s_bMusicMuted = false;
		inline static bool s_bSoundMuted = false;

	};
}