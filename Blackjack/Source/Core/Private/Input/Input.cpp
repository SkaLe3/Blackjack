#include "Input/Input.h"

namespace Core
{

	bool Input::IsKeyPressed(SDL_Keycode keycode)
	{
		 const Uint8* keyState = SDL_GetKeyboardState(NULL);
		 if (keyState[keycode])
		 {
			 return true;
		 }
		 return false;
	}

	bool Input::IsMouseButtonPressed(Uint8 button)
	{
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	glm::vec2 Input::GetMousePosition()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return {x, y};
	}

}