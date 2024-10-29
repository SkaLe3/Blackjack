#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace Core
{
	class Input
	{
	public:
		static bool IsKeyPressed(SDL_Keycode keycode);
		static bool IsMouseButtonPressed(Uint8 button); // SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT
		static glm::vec2 GetMousePosition();
	};
}