#pragma once
#include <iostream>
#include <string>

namespace Core
{
	class Logger
	{
	public:
		enum class LogLevel
		{
			Info,
			Warn,
			Error
		};

		// Main logging function
		static void Log(LogLevel level, const std::string& message);


		template<typename... Args>
		static void Log(LogLevel level, const char* fmt, Args&&... args)
		{
			char buffer[1024];
			snprintf(buffer, sizeof(buffer), fmt, std::forward<Args>(args)...);
			Log(level, std::string(buffer));
		}

	};
}



#ifdef BJ_DEBUG
#define BJ_LOG_INFO(fmt, ...) Core::Logger::Log(Core::Logger::LogLevel::Info, fmt, ##__VA_ARGS__)
#define BJ_LOG_WARN(fmt, ...) Core::Logger::Log(Core::Logger::LogLevel::Warn, fmt, ##__VA_ARGS__)
#define BJ_LOG_ERROR(fmt, ...) Core::Logger::Log(Core::Logger::LogLevel::Error, fmt, ##__VA_ARGS__)
	
#else
#define BJ_LOG_INFO(fmt, ...)
#define BJ_LOG_WARN(fmt, ...) 
#define BJ_LOG_ERROR(fmt, ...) 
#endif
