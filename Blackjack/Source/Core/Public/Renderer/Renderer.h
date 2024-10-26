#pragma once



struct SDL_Renderer;

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
	};

}


