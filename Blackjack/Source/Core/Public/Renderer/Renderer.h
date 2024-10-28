#pragma once



struct SDL_Renderer;
//SDL_ttf testing
struct _TTF_Font;
struct SDL_Texture;

namespace Core
{
	class Renderer
	{
	public:
		static void Init(/* TODO: RendererConfig*/);
		static void Shutdown();

		static void BeginFrame();
		static void EndFrame();

	private:
		inline static SDL_Renderer* s_Renderer;




		static _TTF_Font* BebasFont;
		static SDL_Texture* textureText;
	};

}


