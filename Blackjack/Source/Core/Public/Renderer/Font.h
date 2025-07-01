#pragma once
#include "Core/CoreDefines.h"



#include <memory>

struct _TTF_Font;
typedef _TTF_Font TTF_Font;

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

		bool IsLoaded() const;

	private:
		TTF_Font* m_Font;

		friend class FontManager;
	};

}

