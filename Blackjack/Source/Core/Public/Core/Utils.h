#pragma once
#include "Core/CoreDefines.h"

namespace Core
{
	class Time
	{
	public:
		static float GetTime();
		static float GetTimeMillis();

	private:
		inline static uint64 startTime = 0;
	};
}