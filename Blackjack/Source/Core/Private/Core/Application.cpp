#include "Core/Application.h"

#include "Core/CoreDefines.h"
#include "Renderer/Renderer.h"
#include "Sound/AudioSystem.h"
#include "Core/Utils.h"
#include "Layers/GameLayer.h"
#include "Layers/UILayer.h"
#include "Renderer/FontManager.h"

#include "Renderer/SceneRenderer.h"
#include "Renderer/ScreenRenderer.h"

#include <SDL2/SDL.h>
// Temporary
#include <SDL2/SDL_image.h>

namespace Core
{



	Application* Application::s_Instance = nullptr;

	Application& Application::Get()
	{
		return *s_Instance;
	}

	SharedPtr<ViewportClient> Application::GetViewportClient()
	{
		return std::static_pointer_cast<UILayer>(Application::Get().m_LayerStack.m_Layers[1])->GetViewportClient();
	}

	Application::Application(const ApplicationSpecification& appSpecs)
		: m_Config(appSpecs.AppConfig), m_GPConfig(appSpecs.GPConfig)
	{
		BJ_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		int32 initStatus = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);	
		BJ_ASSERT(initStatus == 0, "Failed to init SDL! SDL_Error: %s", SDL_GetError());

		int32 flags = IMG_INIT_PNG | IMG_INIT_JPG;
		initStatus = IMG_Init(flags);
		BJ_ASSERT((initStatus & flags) == flags, "Failed to init SDL_image! IMG_Error: %s", IMG_GetError());

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		//glEnable(GL_MULTISAMPLE);

		m_Window = Window::Create(appSpecs.WndConfig);
		m_Window->SetEventCallback([this](Event& event) { Application::OnEvent(event); });
		Renderer::Init();

		Renderer::Fonts->AddFontFromFileTTF("BebasNeue-Regular-32", "./Content/Fonts/BebasNeue/BebasNeue-Regular.ttf", 32);
		
		AudioSystem::Init();

		m_AssetManager = MakeUnique<AssetManager>();
		m_AssetManager->SetContentPath("Content");
		m_AssetManager->InitialLoading();
		m_TimerManager = MakeUnique<TimerManager>();
		m_ViewportSystem = MakeUnique<ViewportSystem>();
	}

	Application::~Application()
	{
		Shutdown();
		s_Instance = nullptr;
	}

	SharedPtr<Core::SceneRenderer> Application::GetSceneRenderer()
	{
		return std::static_pointer_cast<GameLayer>(Application::Get().m_LayerStack.m_Layers[0])->GetSceneRenderer();
	}

	SharedPtr<Core::ScreenRenderer> Application::GetScreenRenderer()
	{
		return std::static_pointer_cast<UILayer>(Application::Get().m_LayerStack.m_Layers[1])->GetScreenRenderer();
	}

	void Application::Init()
	{

	}

	void Application::Shutdown()
	{
		AudioSystem::Shutdown();
		Renderer::Shutdown();
		IMG_Quit();
		SDL_Quit();
	}
											
	void Application::Run()
	{
		PushLayer(MakeShared<GameLayer>(m_GPConfig.StartingScene, m_Window->GetWidth(), m_Window->GetHeight()));	   
		PushLayer(MakeShared<UILayer>(m_Window->GetWidth(), m_Window->GetHeight()));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->Init();
		}

		while (m_bRunning)
		{
			float time = Time::GetTime();
			m_DeltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;
			if (m_DeltaTime > 0.05)
			{
				m_DeltaTime = 0.05; // Do not allow big delta time
			}



			ProcessEvents();
			if (!m_bMinimized)
			{

			Renderer::BeginFrame();
			Renderer::Clear();

			for (SharedPtr<Layer> layer : m_LayerStack)
			{
				layer->OnUpdate(m_DeltaTime);
			}

			Renderer::EndFrame();
			}
			else
			{
				SDL_Delay(10);
			}

		}
	}

	void Application::PushLayer(const SharedPtr<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	SharedPtr<Window> Application::GetWindow()
	{
		return m_Window;
	}


	void Application::AskToCloseGame()
	{
		m_bRunning = false;
	}

	void Application::ProcessEvents()
	{
		m_Window->PollEvents();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher disp(event);
		disp.Dispatch(SDL_QUIT, BJ_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.bHandled)
				break;
		}
	}

	bool Application::OnWindowClose(Event& event)
	{
		m_bRunning = false;
		return false;
	}

}

