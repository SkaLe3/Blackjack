#pragma once

#include "Core/CoreDefines.h"
#include <SDL2/SDL.h>


namespace Core
{
	/*
	* @class Texture
	*
	* This class manages the creation, rendering, and destruction of SDL_Texture objects
	*/
	class Texture
	{
	public:
		Texture(SDL_Surface* surface, SDL_Renderer* renderer);
		~Texture();

		SDL_Texture* GetInternal() const;

		int32 GetWidth() const;
		int32 GetHeight() const;

	private:
		SDL_Texture* m_Texture;
		int32 m_Width;
		int32 m_Height;
	};
}