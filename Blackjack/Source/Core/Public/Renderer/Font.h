#pragma once
#include "Core/CoreDefines.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

namespace Core
{
	class Texture;

	/*
	* @class Texture
	* 
	* This class loads a font from a file and provides functionality to render text as a texture
	*/
	class Font
	{
	public:
		Font(const String& fontPath, int32 fontSize);
		~Font();

		// TODO: Move render to FontManager or make it private and class Font as friend of the FontManager
		SharedPtr<Texture> RenderText(const String& text, SDL_Color color);

		bool IsLoaded() const;

	private:
		TTF_Font* m_Font;
	};

}

