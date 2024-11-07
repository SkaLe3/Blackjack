#pragma once
#include "IO/Log.h" 

#ifdef BJ_DEBUG
#define BJ_DEBUGBREAK() __debugbreak()
#define BJ_ENABLE_ASSERTS
#else
#define BJ_DEBUGBREAK()
#endif

#ifdef BJ_DEBUG
#define  BJ_DEBUG_HELPERS 0
#endif

#define DECLARE_SUPER(BaseClass) using Super = BaseClass;

#define BJ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}
#define TIMER_FUNC(func, ...) [=]() { func(__VA_ARGS__); }
#define TIMER_ACTION(action) [=]() { action; }


#include <vector>
#include <functional>

#define DECLARE_DELEGATE_NO_PARAMS(name)                                                          \
struct name                                                                                       \
{                                                                                                 \
public:                                                                                           \
	void Add(std::function<void()> callback) { callbacks.push_back(callback); }                   \
	void Broadcast()                                                                              \
	{                                                                                             \
		for (auto& func : callbacks)                                                              \
		{                                                                                         \
			func();                                                                               \
		}                                                                                         \
	}																							  \
	void Invoke()																				  \
	{																							  \
		Broadcast();																			  \
		Clear();																				  \
	}																							  \
	void Clear()																				  \
	{																							  \
		callbacks.clear();																		  \
	}																							  \
																								  \
private:                                                                                          \
	std::vector<std::function<void()>> callbacks;                                                 \
};

#define DECLARE_DELEGATE_ONE_PARAM(name, P1TYPE)										          \
struct name                                                                                       \
{                                                                                                 \
public:                                                                                           \
	void Add(std::function<void(P1TYPE)> callback) { callbacks.push_back(callback); }             \
	void Broadcast(P1TYPE p1)                                                                     \
	{                                                                                             \
		for (auto& func : callbacks)                                                              \
		{                                                                                         \
			func(p1);                                                                             \
		}                                                                                         \
																						          \
	} 																							  \
	void Invoke(P1TYPE p1)																		  \
	{																						      \
		Broadcast(p1);																		      \
		Clear();																			      \
	}																						      \
		void Clear()																			  \
	{																						      \
		callbacks.clear();																	      \
	}																							  \
																								  \
private:                                                                                          \
	std::vector<std::function<void(P1TYPE)>> callbacks;                                           \
};

#define DECLARE_DELEGATE_TWO_PARAM(name, P1TYPE, P2TYPE)										  \
struct name                                                                                       \
{                                                                                                 \
public:                                                                                           \
	void Add(std::function<void(P1TYPE, P2TYPE)> callback) { callbacks.push_back(callback); }     \
	void Broadcast(P1TYPE p1, P2TYPE p2)                                                          \
	{                                                                                             \
		for (auto& func : callbacks)                                                              \
		{                                                                                         \
			func(p1, p2);                                                                         \
		}                                                                                         \
																						          \
	} 																							  \
	void Invoke(P1TYPE p1, P2TYPE p2)															  \
	{																						      \
		Broadcast(p1, p2);																		  \
		Clear();																			      \
	}																						      \
		void Clear()																			  \
	{																						      \
		callbacks.clear();																	      \
	}																							  \
																								  \
private:                                                                                          \
	std::vector<std::function<void(P1TYPE, P2TYPE)>> callbacks;                                   \
};




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

template<typename T>
using SharedPtr = ::std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr SharedPtr<T> MakeShared(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using WeakPtr = ::std::weak_ptr<T>;

template<typename T>
using UniquePtr = ::std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr UniquePtr<T> MakeUnique(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}



