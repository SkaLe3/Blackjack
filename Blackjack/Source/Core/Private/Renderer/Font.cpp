#include "Renderer/Font.h"

#include "Renderer/Texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Core
{

	Font::Font(const String& fontPath, int32 fontSize)
		: m_Font(nullptr)
	{
	   	m_Font = TTF_OpenFont(fontPath.c_str(), fontSize);
		BJ_ASSERT(m_Font, "Failed to load font: %s", TTF_GetError());
	}

	Font::~Font()
	{
		if (m_Font)
		{
			TTF_CloseFont(m_Font);
		}
	}

	bool Font::IsLoaded() const
	{
		return m_Font != nullptr;
	}

}