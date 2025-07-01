#include "Sound/Sound.h"


namespace Core
{

	bool SoundBase::IsOneShot() const
	{
		return m_bOneShot;
	}

	void SoundBase::SetOneShot(bool os)
	{
		m_bOneShot = os;
	}


	float SoundBase::GetVolumeMultiplier()
	{
		return 1.0f;
	}


	void SoundBase::SetVolumeMultiplier(float volume)
	{
		m_VolumeMultiplier = std::min(std::max(volume, 0.0f), 1.0f);
	}

	SoundCue::SoundCue(Mix_Chunk* chunk) : m_Chunk(chunk)
	{
		m_bOneShot = true;
	}

	SoundCue::~SoundCue()
	{
	   Mix_FreeChunk(m_Chunk);
	}

	float SoundCue::GetVolumeMultiplier()
	{
		 return m_VolumeMultiplier;
	}

	SoundMusic::SoundMusic(Mix_Music* music)
	{
		m_bOneShot = false;
		m_Music = music;
	}

	SoundMusic::~SoundMusic()
	{
	   Mix_FreeMusic(m_Music);
	}

	float SoundMusic::GetVolumeMultiplier()
	{
		return m_VolumeMultiplier;
	}


}