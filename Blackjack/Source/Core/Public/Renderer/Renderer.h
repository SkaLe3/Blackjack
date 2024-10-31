#pragma once
#include "Renderer/FontManager.h"

#include <glm/glm.hpp>
#include <memory>


struct SDL_Renderer;
struct SDL_Surface;
class SceneRenderer;

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

		static SharedPtr<Texture> CreateTextureFromSurface(SDL_Surface* surface);

		static SDL_Renderer* DebugGetRenderer() { return s_Renderer; }

		static void Clear();
		static void DrawTexturedRect(SharedPtr<Texture> texture, const glm::vec4& source, const glm::vec4 target, const glm::vec4 color);
		static void DrawRect(const glm::vec4 target, const glm::vec4 color);

	public:
		static UniquePtr<FontManager> Fonts;

	private:
		inline static SDL_Renderer* s_Renderer;

		friend SceneRenderer;
	};

}


