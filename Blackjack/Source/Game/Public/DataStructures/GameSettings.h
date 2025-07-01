#pragma once
#include "Sound/ActiveSound.h"
class GameSettings
{
public:
	static inline Core::ActiveSound AmbientSoundActive;
	static inline SharedPtr<Core::SoundBase> AmbientSound;
	static inline bool bAmbientMuted = false;
};