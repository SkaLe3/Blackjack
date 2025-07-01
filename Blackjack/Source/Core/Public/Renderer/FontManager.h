#pragma once
#include "Core/CoreDefines.h"

#include "Renderer/Font.h"
#include <unordered_map>
#include <memory>
#include "glm/glm.hpp"


namespace Core
{
	/*
	* @class FontManager
	* 
	* This class loads and retrieves fonts by ID
	*/
	class FontManager
	{
	public:
		FontManager();
		~FontManager();

		static UniquePtr<FontManager> Create(); 

		/** First added font becomes active */
		bool AddFontFromFileTTF(const String& fontId, const String& fontPath, int fontSize);
		Font* GetFont(const String& fontId);
		Font* GetActiveFont();
		String GetActiveFontID();
		bool SelectFont(const String& fontId);

		SharedPtr<Texture> RenderText(const String& text, const glm::vec4& color);

	private:
		std::unordered_map<String, SharedPtr<Font>> m_FontAtlas;
		String m_ActiveFontId;
	};
}