#pragma once
#include "IO/Log.h"

#ifdef BJ_DEBUG
	#define BJ_DEBUGBREAK() __debugbreak()
	#define BJ_ENABLE_ASSERTS
#else
	#define BJ_DEBUGBREAK()
#endif


#define VM_BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}

#ifdef BJ_ENABLE_ASSERTS
	#define BJ_ASSERT(condition, message) do { if (!(condition)) { std::cout << "Assertion failed: " << (message) << "\n"; BJ_DEBUGBREAK(); }} while (false) 
#else
	#define BJ_ASSERT(condition, message)
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


