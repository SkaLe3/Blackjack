#pragma once
#include "Sound/Sound.h"

namespace Core
{
	class ActiveSound
	{
	public:
		ActiveSound() : Sound(nullptr), Channel(-1){}
		ActiveSound(SharedPtr<SoundCue> sound, int32 channel) : Sound(sound), Channel(channel){}

		SharedPtr<SoundCue> Sound;
		int32 Channel;
	};
}