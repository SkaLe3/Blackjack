#include "Core/Utils.h"
#include <SDL2/SDL.h>
#include <nfd.h>


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

