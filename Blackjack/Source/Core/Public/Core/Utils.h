#pragma once
#include "Core/CoreDefines.h"

#include <glm/glm.hpp>

namespace Core
{
	inline glm::vec2 Lerp(const glm::vec2& start, const glm::vec2& target, float t)
	{
		return (1.0f - t) * start + t * target;
	}
	inline float Lerp(float start, float target, float t)
	{
		return (1.0f - t) * start + t * target;
	}

	inline float EaseInOutQuad(float t)
	{
		return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
	}

	inline float EaseInOutCubic(float t)
	{
		return t < 0.5f ? 4 * t * t * t : (t - 1) * (2 * t - 2) * (2 * t - 2) + 1;
	}


	class Time
	{
	public:
		static float GetTime();
		static float GetTimeMillis();

	private:
		inline static uint64 startTime = 0;
	};
}