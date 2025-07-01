#include "Renderer/FontManager.h"

#include "Renderer/Renderer.h"
#include "Core/Application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Core
{

	FontManager::FontManager()
	{
		int32 initStatus = TTF_Init();
		BJ_ASSERT(initStatus == 0, "Failed to initialize SDL_ttf: %s", TTF_GetError());
	}

	FontManager::~FontManager()
	{
		m_FontAtlas.clear();
		TTF_Quit();
	}

	UniquePtr<FontManager> FontManager::Create()
	{
		return MakeUnique<FontManager>();
	}

	bool FontManager::AddFontFromFileTTF(const String& fontId, const String& fontPath, int fontSize)
	{
		auto font = MakeShared<Font>(fontPath, fontSize);
		if (!font->IsLoaded())
		{
			return false;
		}
		m_FontAtlas[fontId] = std::move(font);
		if (m_FontAtlas.size() == 1)
		{
			m_ActiveFontId = fontId;
		}
		return true;
	}

	Font* FontManager::GetFont(const String& fontId)
	{
		if (auto it = m_FontAtlas.find(fontId); it != m_FontAtlas.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

	Font* FontManager::GetActiveFont()
	{
		return GetFont(m_ActiveFontId);
	}

	String FontManager::GetActiveFontID()
	{
		return m_ActiveFontId;
	}

	bool FontManager::SelectFont(const String& fontId)
	{
		if (auto it = m_FontAtlas.find(fontId); it != m_FontAtlas.end())
		{
			m_ActiveFontId = it->first;
			return true;
		}
		return false;
	}

	SharedPtr<Texture> FontManager::RenderText(const String& text, const glm::vec4& color)
	{
		SharedPtr<Font> activeFont = m_FontAtlas[m_ActiveFontId];
		if (!activeFont->IsLoaded()) return nullptr;

		SDL_Surface* textSurface = TTF_RenderText_Blended(activeFont->m_Font, text.c_str(), {uint8(255.f * color.x), uint8(255.f * color.y), uint8(255.f * color.z), uint8(255.f * color.w)});
		BJ_ASSERT(textSurface, "Failed to render text surface: %s", TTF_GetError());

		auto texture = Renderer::CreateTextureFromSurface(textSurface);
		SDL_FreeSurface(textSurface);

		return texture;
	}

}