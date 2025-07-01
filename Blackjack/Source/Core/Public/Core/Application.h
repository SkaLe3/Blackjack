#pragma once

#include "Core/CoreDefines.h"
#include "Core/Window.h"
#include "Layers/LayerStack.h"
#include "Core/Event.h"
#include "Core/AssetManager.h"
#include "Core/TimerManager.h"
#include "Renderer/FontManager.h"
#include "World/World/World.h"
#include "Renderer/Texture.h" // Temporary

#include "UISystem/ViewportSystem.h"

#include <filesystem>
#include <memory>
#include <functional>


namespace Core
{
	struct ApplicationConfig
	{
		String Name = "Blackjack";
		std::filesystem::path ContentPath;
	};

	struct GameplayConfig
	{
		std::function<SharedPtr<World>()> StartingScene;
	};

	struct ApplicationSpecification
	{
		ApplicationConfig AppConfig;
		WindowConfig WndConfig;
		GameplayConfig GPConfig;
	};
	
	class ViewportClient;
	class SceneRenderer;
	class ScreenRenderer;

	class Application
	{
	public:
		static Application& Get();
		static SharedPtr<ViewportClient> GetViewportClient();

	public:
		Application(const ApplicationSpecification& appSpecs);
		virtual ~Application();

		SharedPtr<SceneRenderer> GetSceneRenderer();
		SharedPtr<ScreenRenderer> GetScreenRenderer();


		void Init();
		void Shutdown();
		void Run();
		void PushLayer(const SharedPtr<Layer> layer);

		SharedPtr<Window> GetWindow();

		void AskToCloseGame();
	private:
		void ProcessEvents();
		void OnEvent(Event& event);
		bool OnWindowClose(Event& event);


	private:
		static Application* s_Instance;

	private:
		ApplicationConfig m_Config;
		GameplayConfig m_GPConfig;
		LayerStack m_LayerStack;

		bool m_bRunning = true;
		bool m_bMinimized = false;

		float m_DeltaTime = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		SharedPtr<Window> m_Window;
		UniquePtr<AssetManager> m_AssetManager;
		UniquePtr<TimerManager> m_TimerManager;
		UniquePtr<ViewportSystem> m_ViewportSystem;


		friend AssetManager;
		friend TimerManager;
	};

	Application* CreateApplication(const std::vector<std::string>& arguments);
}