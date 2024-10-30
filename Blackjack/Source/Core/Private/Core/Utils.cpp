#include "Core/Utils.h"
#include <SDL2/SDL.h>

namespace Core
{

	float Time::GetTime()
	{
		  Uint64 currentTime = SDL_GetPerformanceCounter();
		  return static_cast<float>((float)(currentTime - startTime) / (float)SDL_GetPerformanceFrequency());
	}

	float Time::GetTimeMillis()
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		return static_cast<float>((float)(currentTime - startTime) * 1000 / (float)SDL_GetPerformanceFrequency());
	}
}

