#pragma once
#include "Core/CoreDefines.h"
#include <functional>
#include <memory>

#include <SDL2/SDL.h>


struct SDL_Window;

namespace Core
{
	using EventCallbackFN = std::function<void(SDL_Event&)>;

	struct WindowConfig
	{
		String Title = "Window";
		uint32 Width = 1280;
		uint32 Height = 720;
		bool VSync = true;
	};

	class Window
	{
	public:
		Window(const WindowConfig& config);
		~Window() {}

		static std::shared_ptr<Window> Create(const WindowConfig& config);

		void PollEvents();

		uint32 GetWidth() const { return m_Data.Width; }
		uint32 GetHeight() const { return m_Data.Height; }
		bool IsVSyncEnabled() const { return m_Data.VSync; }
		SDL_Window* GetNativeWindow() const;

		void SetEventCallback(const EventCallbackFN& callback);

	private:
		bool Init(const WindowConfig& config);
		void Shutdown();

	private:
		struct WindowData
		{
			uint32 Width;
			uint32 Height;
			bool VSync;

			EventCallbackFN EventCallback = [](SDL_Event& event) {};

			// TODO: Add callback
		};
		WindowData m_Data;

		SDL_Window* m_Window;
	};
}