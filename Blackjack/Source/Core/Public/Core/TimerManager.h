#pragma once
#include "Core/CoreDefines.h"
#include <functional>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <atomic>
#include <mutex>
#include <future>

namespace Core
{
	using TimerHandle = int;
	class TimerManager
	{
	public:
		static TimerManager& Get();
	public:
		using TimerCallback = std::function<void()>;


		TimerManager() : nextHandle(1), isRunning(true)
		{
			managerThread = std::thread([this]() { Run(); });
		}

		~TimerManager()
		{
			// Stop all timers and the manager thread
			isRunning = false;
			if (managerThread.joinable())
			{
				managerThread.join();
			}
		}

		// TODO: switch interval and callback 
		// TODO: Use time in seconds
		// Starts a timer with the specified interval, callback, loop flag, and start delay flag
		TimerHandle StartTimer(int interval, TimerCallback callback, bool loop = false, bool delayFirstCall = true)
		{
			std::lock_guard<std::recursive_mutex> lock(mutex);

			TimerHandle handle = nextHandle++;
			TimerData timerData = { interval, std::move(callback), loop, delayFirstCall, std::chrono::steady_clock::now() };

			timers[handle] = std::move(timerData);
			return handle;
		}

		// Stops and removes a timer with the specified handle
		bool ClearTimer(TimerHandle handle)
		{
			std::lock_guard<std::recursive_mutex> lock(mutex);
			return timers.erase(handle) > 0;
		}

		// Clears all active timers
		void ClearAllTimers()
		{
			std::lock_guard<std::recursive_mutex> lock(mutex);
			timers.clear();
		}

	private:
		struct TimerData
		{
			int interval;
			TimerCallback callback;
			bool loop;
			bool delayFirstCall;
			std::chrono::steady_clock::time_point lastExecution;
		};

		std::unordered_map<TimerHandle, TimerData> timers;
		std::recursive_mutex mutex;
		std::atomic<bool> isRunning;
		std::thread managerThread;
		std::atomic<int> nextHandle;


		void Run()
		{
			while (isRunning)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));

				auto now = std::chrono::steady_clock::now();
				std::lock_guard<std::recursive_mutex> lock(mutex);

				for (auto it = timers.begin(); it != timers.end();)
				{
					TimerData& timer = it->second;
					auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timer.lastExecution).count();

					// If delayFirstCall is false and first execution, invoke immediately
					if (!timer.delayFirstCall && timer.lastExecution == it->second.lastExecution)
					{
						timer.callback();
						timer.lastExecution = std::chrono::steady_clock::now();
						timer.delayFirstCall = true;  // Ensures that future calls respect the interval
						if (!timer.loop)
						{
							it = timers.erase(it);
							continue;
						}
					}
					else if (elapsed >= timer.interval)
					{
						timer.callback();
						timer.lastExecution = now;

						// If timer is not looping, remove it after execution
						if (!timer.loop)
						{
							it = timers.erase(it);
							continue;
						}
					}
					++it;
				}
			}
		}
	};
}