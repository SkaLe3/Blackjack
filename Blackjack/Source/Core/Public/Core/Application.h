#include "Core/CoreDefines.h"
#include "Core/Window.h"
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

	private:
		static Application* s_Instance;

	private:
		ApplicationConfig m_Config;
	
		bool m_bRunning = true;
		bool m_bMinimized = false;

		float m_DeltaTime = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		std::unique_ptr<Window> m_Window;
		SDL_Renderer* m_Renderer;
	};

	Application* CreateApplication(int argc, char** argv);
}