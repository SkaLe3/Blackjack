#include "Core/Utils.h"
#include <SDL2/SDL.h>

namespace Core
{
	float Time::GetTime()
	{
		  return SDL_GetTicks();
	}
}

