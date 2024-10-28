#pragma once
#include "Renderer/FontManager.h"

#include <memory>

struct SDL_Renderer;
struct SDL_Surface;

namespace Core
{
	class Texture;

	class Renderer
	{
	public:
		static void Init(/* TODO: RendererConfig*/);
		static void Shutdown();

		static void BeginFrame();
		static void EndFrame();

		static SharedPtr<Texture>	CreateTextureFromSurface(SDL_Surface* surface);

		static SDL_Renderer* DebugGetRenderer() { return s_Renderer; }

	public:
		static UniquePtr<FontManager> Fonts;

	private:
		inline static SDL_Renderer* s_Renderer;
	};

}


