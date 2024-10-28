#pragma once
#include "IO/Log.h"

#ifdef BJ_DEBUG
    #define BJ_DEBUGBREAK() __debugbreak()
    #define BJ_ENABLE_ASSERTS
#else
    #define BJ_DEBUGBREAK()
#endif


#define BJ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}

// Helper function to print formatted messages
template<typename... Args>
void PrintFormatted(const char* format, Args... args)
{
	// Buffer for formatted message
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), format, args...);
	std::cout << buffer; // Print the formatted message
}

#ifdef BJ_ENABLE_ASSERTS
#define BJ_ASSERT(condition, ...) do { \
        if (!(condition)) { \
            std::cout << "Assertion failed: " << #condition << "\n" \
                      << "Message: "; \
            PrintFormatted(__VA_ARGS__); \
            std::cout << "\nFile: " << __FILE__ << "\n" \
                      << "Line: " << __LINE__ << "\n" \
                      << "Function: " << __FUNCTION__ << std::endl; \
            BJ_DEBUGBREAK(); \
            std::exit(EXIT_FAILURE);  \
        } \
    } while (false)
#else
#define BJ_ASSERT(condition, ...)
#endif



#include <memory>
#include <string>
#include <filesystem>
#include <cstdint>


using byte = uint8_t;
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using size_t = ::std::size_t;

using String = ::std::string;


