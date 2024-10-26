#include "Core/Application.h"
#include "Core/CoreDefines.h"

// Temporary
#include <SDL2/SDL.h>


namespace Core
{
	Application* Application::s_Instance = nullptr;

	Application& Application::Get()
	{
		return *s_Instance;
	}

	Application::Application(const ApplicationSpecification& appSpecs)
		: m_Config(appSpecs.AppConfig)
	{
		BJ_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(appSpecs.WndConfig);

		m_Renderer = SDL_CreateRenderer(m_Window->GetNativeWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_Renderer)
		{
			BJ_LOG("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()))
			SDL_DestroyWindow(m_Window->GetNativeWindow());
			SDL_Quit();
			return;
		}

		SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 255);
	}

	Application::~Application()
	{
		Shutdown();
		s_Instance = nullptr;
	}

	void Application::Init()
	{

	}

	void Application::Shutdown()
	{
		SDL_DestroyRenderer(m_Renderer);
		SDL_Quit();
	}

	void Application::Run()
	{
		SDL_Event event;
		while (m_bRunning)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					m_bRunning = false;
			}
			m_Window->PollEvents();

			SDL_SetRenderDrawColor(m_Renderer, 200, 200, 200, 255);
			SDL_RenderClear(m_Renderer);
			SDL_RenderPresent(m_Renderer);

		}
	}

}

