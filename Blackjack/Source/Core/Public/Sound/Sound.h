#pragma once
#include "Core/CoreDefines.h"

#include <SDL2/SDL_mixer.h>

namespace Core
{
	class AudioSystem;

	class SoundBase
	{
	public:
		SoundBase() = default;
		virtual ~SoundBase() = default;

		virtual bool IsOneShot() const;
		void SetOneShot(bool os);

		virtual float GetVolumeMultiplier();

	protected:
		bool m_bOneShot = true;
		float m_VolumeMultiplier = 1.0f;

		friend AudioSystem;

	};


	class SoundCue : public SoundBase
	{
	public:
		SoundCue(Mix_Chunk* chunk);
		~SoundCue();

		//~ Begin SoundBase Interface
		virtual float GetVolumeMultiplier() override;
		//~ End SoundBase Interface

		inline Mix_Chunk* Get() { return m_Chunk; }

	private:
		Mix_Chunk* m_Chunk;

	};

	class SoundMusic : public SoundBase
	{
	public:
		SoundMusic(Mix_Music* music);
		~SoundMusic();

		//~ Begin SoundBase Interface
		virtual float GetVolumeMultiplier() override;
		//~ End SoundBase Interface

		inline Mix_Music* Get() { return m_Music; }
		inline float GetActivetedVolume() { return m_ActivetedVolume; }
		void OnPlayed(float volume) { m_ActivetedVolume = volume; }
	private:
		Mix_Music* m_Music;
		float m_ActivetedVolume = 1.0f; /** Volume that was passed to PlayMusic function */

	};
}