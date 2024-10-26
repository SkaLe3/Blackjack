#pragma once
#include "Core/Window.h"
#include <SDL2/SDL.h>

namespace Core
{

	Window::Window(const WindowConfig& config)
	{
		WindowData WD
		{
		 .Width = config.Width,
		 .Height = config.Height,
		 .VSync = config.VSync,
		};
		m_Data = WD;
		Init(config);
	}

	std::shared_ptr<Window> Window::Create(const WindowConfig& config)
	{
		 return std::make_shared<Window>(config);
	}


	void Window::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			m_Data.EventCallback(event);
		}

	}

	SDL_Window* Window::GetNativeWindow() const
	{
		return m_Window;
	}

	void Window::SetEventCallback(const EventCallbackFN& callback)
	{
		m_Data.EventCallback = callback;
	}

	bool Window::Init(const WindowConfig& config)
	{
		BJ_LOG_INFO("Creating Window %s (%d, %d)", config.Title.c_str(), config.Width, config.Height);


		m_Window = SDL_CreateWindow(config.Title.c_str(), SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, config.Width, config.Height,
									SDL_WINDOW_SHOWN);

		BJ_ASSERT(m_Window, "Failed to create window! SDL_Error: %s", SDL_GetError());

		return true;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
	}

}