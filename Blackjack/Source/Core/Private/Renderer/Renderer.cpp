 #include "Renderer/Renderer.h"

 #include "Core/Application.h"

 #include <SDL2/SDL.h>


namespace Core
{

	void Renderer::Init(/* TODO: RendererConfig*/)
	{
		std::shared_ptr<Window> window = Application::Get().GetWindow();
		int vsyncFlag = window->IsVSyncEnabled() ? SDL_RENDERER_PRESENTVSYNC : 0;
		s_Renderer = SDL_CreateRenderer(window->GetNativeWindow(), -1, SDL_RENDERER_ACCELERATED | vsyncFlag);
		BJ_ASSERT(s_Renderer, "Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
		SDL_SetRenderDrawColor(s_Renderer, 200, 200, 200, 255);
	}

	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(s_Renderer);
	}

	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(s_Renderer, 200, 200, 200, 255);
		SDL_RenderClear(s_Renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(s_Renderer);
	}

}

