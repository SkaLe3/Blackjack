#pragma once

#include "Core/CoreDefines.h"
#include "Core/Window.h"
#include "Renderer/Texture.h" // Temporary

#include <SDL2/SDL.h>


#include <filesystem>
#include <memory>


struct SDL_Window;
struct SDL_Renderer;

namespace Core
{
	struct ApplicationConfig
	{
		String Name = "Blackjack";
		std::filesystem::path ContentPath;
	};

	struct ApplicationSpecification
	{
		ApplicationConfig AppConfig;
		WindowConfig WndConfig;
	};
	


	class Application
	{
	public:
		static Application& Get();

	public:
		Application(const ApplicationSpecification& appSpecs);
		virtual ~Application();

		void Init();
		void Shutdown();

		void Run();

		std::shared_ptr<Window> GetWindow();

	private:
		void ProcessEvents();
		void OnEvent(SDL_Event event);

		void OnWindowClose(SDL_Event& event);

	private:
		static Application* s_Instance;

	private:
		ApplicationConfig m_Config;
	
		bool m_bRunning = true;
		bool m_bMinimized = false;

		float m_DeltaTime = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		std::shared_ptr<Window> m_Window;
		std::shared_ptr<Texture> textTex;
	};

	Application* CreateApplication(int argc, char** argv);
}