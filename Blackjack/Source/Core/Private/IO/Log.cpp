#include "IO/Log.h"

#include <SDL2/SDL.h>
namespace Core
{

	void Logger::Log(LogLevel level, const std::string& message)
	{
		{
			switch (level)
			{
			case LogLevel::Info:
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
				break;
			case LogLevel::Warn:
				SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
				break;
			case LogLevel::Error:
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
				break;
			}
		}
	}
}


