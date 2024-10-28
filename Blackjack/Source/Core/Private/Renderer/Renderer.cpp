#include "Renderer/Renderer.h"

#include "Core/Application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>



#include <filesystem>
#include <iostream>


namespace Core
{

	void Renderer::Init(/* TODO: RendererConfig*/)
	{
		std::shared_ptr<Window> window = Application::Get().GetWindow();
		int vsyncFlag = window->IsVSyncEnabled() ? SDL_RENDERER_PRESENTVSYNC : 0;
		s_Renderer = SDL_CreateRenderer(window->GetNativeWindow(), -1, SDL_RENDERER_ACCELERATED | vsyncFlag);
		BJ_ASSERT(s_Renderer, "Renderer could not be created! SDL_Error: %s", SDL_GetError());
		SDL_SetRenderDrawColor(s_Renderer, 200, 200, 200, 255);


		int status = TTF_Init();
		BJ_ASSERT(status == 0, "Could not initialize SDL2_ttf, error: %s", TTF_GetError());

		std::filesystem::path cwd = std::filesystem::current_path();
		std::cout << "Current working directory: " << cwd << std::endl;

		BebasFont = TTF_OpenFont("./Content/Fonts/BebasNeue-Regular.ttf", 32);
		BJ_ASSERT(BebasFont, "Could not load font: %s", "./Fonts/BebasNeue-Regular.ttf");

		SDL_Surface* surfaceText = TTF_RenderText_Solid(BebasFont, "Blackjack game", { 255, 255, 255 });
		textureText = SDL_CreateTextureFromSurface(s_Renderer, surfaceText);
		SDL_FreeSurface(surfaceText);


	}

	void Renderer::Shutdown()
	{
		SDL_DestroyTexture(textureText);
		TTF_CloseFont(BebasFont);
		TTF_Quit();
		SDL_DestroyRenderer(s_Renderer);
	}

	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(s_Renderer, 200, 200, 200, 255);
		SDL_RenderClear(s_Renderer);


		SDL_Rect txtRect{
	.x = 10,
	.y = 10,
	.w = 400,
	.h = 100,
		};

		SDL_RenderCopy(s_Renderer, textureText, NULL, &txtRect);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(s_Renderer);
	}

	TTF_Font* Renderer::BebasFont;

	SDL_Texture* Renderer::textureText;

}

