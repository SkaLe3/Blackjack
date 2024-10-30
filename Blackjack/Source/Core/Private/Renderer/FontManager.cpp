#include "Renderer/FontManager.h"

namespace Core
{

	FontManager::FontManager()
	{
		int32 initStatus = TTF_Init();
		BJ_ASSERT(initStatus == 0, "Failed to initialize SDL_ttf: %s", TTF_GetError());
	}

	FontManager::~FontManager()
	{
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

	bool FontManager::SelectFont(const String& fontId)
	{
		if (auto it = m_FontAtlas.find(fontId); it != m_FontAtlas.end())
		{
			m_ActiveFontId = it->first;
			return true;
		}
		return false;
	}

}