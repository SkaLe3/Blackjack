#include "Renderer/Renderer.h"

#include "Renderer/Texture.h"

#include "Core/Application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <filesystem>
#include <iostream>


namespace Core
{
	UniquePtr<FontManager> Renderer::Fonts = nullptr;

	void Renderer::Init(/* TODO: RendererConfig*/)
	{
		SharedPtr<Window> window = Application::Get().GetWindow();

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		int vsyncFlag = window->IsVSyncEnabled() ? SDL_RENDERER_PRESENTVSYNC : 0;
		s_Renderer = SDL_CreateRenderer(window->GetNativeWindow(), 3, SDL_RENDERER_ACCELERATED | vsyncFlag);
		BJ_ASSERT(s_Renderer, "Renderer could not be created! SDL_Error: %s", SDL_GetError());

		// Uncomment if needed
		//SDL_RenderSetLogicalSize(s_Renderer, 1920, 1080);

		SDL_RendererInfo info;
		SDL_GetRendererInfo(s_Renderer, &info);
		BJ_LOG_INFO("Renderer created. Using %s API", info.name);

		int Buffers, Samples;
		SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &Buffers);
		SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &Samples);
		BJ_LOG_INFO("Multisample buffers: %d", Buffers);
		BJ_LOG_INFO("Nultisample samples: %d", Samples);

		SDL_SetRenderDrawColor(s_Renderer, 200, 200, 200, 255);

		Fonts = FontManager::Create();
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

	SharedPtr<Texture> Renderer::CreateTextureFromSurface(SDL_Surface* surface)
	{
		return MakeShared<Texture>(surface, s_Renderer);
	}

}

