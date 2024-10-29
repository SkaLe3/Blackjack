#include "Core/Utils.h"
#include <SDL2/SDL.h>

namespace Core
{

	float Time::GetTime()
	{
		  Uint64 currentTime = SDL_GetPerformanceCounter();
		  return static_cast<float>((currentTime - startTime) / SDL_GetPerformanceFrequency());
	}

	float Time::GetTimeMillis()
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		return static_cast<float>((currentTime - startTime) * 1000 / SDL_GetPerformanceFrequency());
	}
}

