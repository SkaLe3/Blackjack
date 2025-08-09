#include "Core/Utils.h"
#include <SDL2/SDL.h>
#include <nfd.h>


namespace Core
{

	uint64 Time::GetTime()
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		return static_cast<uint64>((currentTime - startTime) * 1000 / SDL_GetPerformanceFrequency()) / 1000.f;
	}

	uint64 Time::GetTimeMillis()
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		return static_cast<uint64>((currentTime - startTime) * 1000 / SDL_GetPerformanceFrequency());
	}

	String FileDialogs::OpenFile(const char* filter)
	{
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_OpenDialog("png", NULL, &outPath);

		if (result == NFD_OKAY)
		{
			BJ_LOG_INFO("Success!");
			BJ_LOG_INFO("%s", outPath);
			return String(outPath);
		}
		else if (result == NFD_CANCEL)
		{
			return String();
		}
		else
		{
			BJ_LOG_ERROR("Error: %s\n", NFD_GetError());
			return String();
		}

	}

}

