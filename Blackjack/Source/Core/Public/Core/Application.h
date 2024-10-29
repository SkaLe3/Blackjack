#pragma once

#include "Core/CoreDefines.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Core/Event.h"
#include "Renderer/Texture.h" // Temporary



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

		SharedPtr<Window> GetWindow();

	private:
		void ProcessEvents();
		void OnEvent(Event& event);

		bool OnWindowClose(Event& event);

	private:
		static Application* s_Instance;

	private:
		ApplicationConfig m_Config;
		LayerStack m_LayerStack;

		bool m_bRunning = true;
		bool m_bMinimized = false;

		float m_DeltaTime = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		SharedPtr<Window> m_Window;

		// Temporary
		SharedPtr<Texture> textTex;
		SharedPtr<Texture> chipTex;
	};

	Application* CreateApplication(int argc, char** argv);
}