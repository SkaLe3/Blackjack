#include "Core/Application.h"

#include "Core/CoreDefines.h"
#include "Renderer/Renderer.h"
#include "Core/Utils.h"

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

		int status = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
		
			
		BJ_ASSERT(status == 0, "Failed to init SDL! SDL_Error: %s", SDL_GetError());

		m_Window = Window::Create(appSpecs.WndConfig);
		m_Window->SetEventCallback([this](SDL_Event& event) { Application::OnEvent(event); });
		Renderer::Init();
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
		SDL_Quit();
	}

	void Application::Run()
	{

		while (m_bRunning)
		{
			float time = Time::GetTime();
			m_DeltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;


			m_Window->PollEvents();

			Renderer::BeginFrame();

			Renderer::EndFrame();

		}
	}

	std::shared_ptr<Window> Application::GetWindow()
	{
		return m_Window;
	}


	void Application::ProcessEvents()
	{
		m_Window->PollEvents();
	}

	void Application::OnEvent(SDL_Event event)
	{
		if (event.type == SDL_QUIT)
			OnWindowClose(event);
	}

	void Application::OnWindowClose(SDL_Event& event)
	{
		m_bRunning = false;
	}

}

