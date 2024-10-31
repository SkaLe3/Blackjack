#pragma once
#include "Core/CoreDefines.h"
#include "Core/AssetManager.h"

namespace Core
{
	class ISound
	{
	public:
		virtual ~ISound() = default;

		virtual void PlaySound() = 0;
		virtual void StopSound() = 0;
	};


	class SoundCue : public ISound
	{
	public:
		SoundCue(SDL_AudioSpec spec, byte* start, uint32 len) : m_AudioSpec(spec), m_WaveStart(start), m_WaveLenght(len) {}
		~SoundCue() {}

		virtual void PlaySound() override {}
		virtual void StopSound() override {}
		void SetupDevice() {}

	private:
		SDL_AudioDeviceID m_Device;

		SDL_AudioSpec m_AudioSpec;
		byte* m_WaveStart;
		uint32 m_WaveLenght;
	};
}