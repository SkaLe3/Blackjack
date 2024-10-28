#pragma once
#include "Core/CoreDefines.h"

#include "Renderer/Font.h"
#include <unordered_map>
#include <memory>


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

		static std::unique_ptr<FontManager> Create(); 

		/** First added font becomes active */
		bool AddFontFromFileTTF(const String& fontId, const String& fontPath, int fontSize);
		Font* GetFont(const String& fontId);
		Font* GetActiveFont();
		bool SelectFont(const String& fontId);

	private:
		std::unordered_map<String, std::unique_ptr<Font>> m_FontAtlas;
		String m_ActiveFontId;
	};
}