#include "Core/Application.h"

#include "Core/CoreDefines.h"
#include "Renderer/Renderer.h"
#include "Core/Utils.h"

// Temporary
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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

		int32 initStatus = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);	
		BJ_ASSERT(initStatus == 0, "Failed to init SDL! SDL_Error: %s", SDL_GetError());

		int32 flags = IMG_INIT_PNG | IMG_INIT_JPG;
		initStatus = IMG_Init(flags);
		BJ_ASSERT((initStatus & flags) == flags, "Failed to init SDL_image! IMG_Error: %s", IMG_GetError());



		m_Window = Window::Create(appSpecs.WndConfig);
		m_Window->SetEventCallback([this](Event& event) { Application::OnEvent(event); });
		Renderer::Init();

		Renderer::Fonts->AddFontFromFileTTF("BebasNeue-32", "./Content/Fonts/BebasNeue-Regular.ttf", 32);
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
		IMG_Quit();
		SDL_Quit();
	}

	void Application::Run()
	{
		// Font rendering example
		textTex = Renderer::Fonts->GetActiveFont()->RenderText("Blackjack", { 0, 0, 0 });

		// Texture loading example
		chipTex = Renderer::CreateTextureFromFile("./Content/Textures/RedChip.png");


		while (m_bRunning)
		{
			float time = Time::GetTime();
			m_DeltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;



			m_Window->PollEvents();
			if (!m_bMinimized)
			{

			Renderer::BeginFrame();

			for (SharedPtr<Layer> layer : m_LayerStack)
			{
				layer->OnUpdate(m_DeltaTime);
			}

			// Text rendering example
			// Will be moved to the Renderer class
			SDL_Rect textRect{
				.x = 10,
				.y = 10,
				.w = textTex->GetWidth(),
				.h = textTex->GetHeight(),
			};
			SDL_Rect chipRect{
				.x = 200,
				.y = 300,
				.w = 200,
				.h = 200,
			};

			SDL_SetRenderDrawColor(Renderer::DebugGetRenderer(), 200, 50, 50, 255);
			SDL_RenderDrawRect(Renderer::DebugGetRenderer(), &textRect);

			SDL_RenderCopy(Renderer::DebugGetRenderer(), textTex->GetInternal(), NULL, &textRect);
			SDL_RenderCopy(Renderer::DebugGetRenderer(), chipTex->GetInternal(), NULL, &chipRect);

			Renderer::EndFrame();
			}
			else
			{
				SDL_Delay(10);
			}

		}
	}

	SharedPtr<Window> Application::GetWindow()
	{
		return m_Window;
	}


	void Application::ProcessEvents()
	{
		m_Window->PollEvents();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher disp(event);
		disp.Dispatch(SDL_QUIT, BJ_BIND_EVENT_FN(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(Event& event)
	{
		m_bRunning = false;
		return false;
	}

}

