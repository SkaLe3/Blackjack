#include "Renderer/Font.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

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

	SharedPtr<Texture> Font::RenderText(const String& text, SDL_Color color)
	{
		if (!m_Font) return nullptr;

		SDL_Surface* textSurface = TTF_RenderText_Blended(m_Font, text.c_str(), color);
		BJ_ASSERT(textSurface, "Failed to render text surface: %s", TTF_GetError());

		auto texture = Renderer::CreateTextureFromSurface(textSurface);
		SDL_FreeSurface(textSurface);

		return texture;
	}

	bool Font::IsLoaded() const
	{
		return m_Font != nullptr;
	}

}