#pragma once

#include "Core/CoreDefines.h"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>


namespace Core
{
	/*
	* @class Texture
	*
	* Manages the creation, rendering, and destruction of SDL_Texture objects.
	* Note: The surface resource is not managed by this class; the caller is responsible for handling it.
	*/
	class Texture
	{
	public:
		/** Constructs a Texture from an SDL_Surface and SDL_Renderer, managing the SDL_Texture lifecycle. */
		Texture(SDL_Surface* surface, SDL_Renderer* renderer);
		~Texture();

		SDL_Texture* GetInternal() const;

		int32 GetWidth() const;
		int32 GetHeight() const;

		glm::vec2 GetSize() const;

	private:
		SDL_Texture* m_Texture;
		int32 m_Width;
		int32 m_Height;
	};
}