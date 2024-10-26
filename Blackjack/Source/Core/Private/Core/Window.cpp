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

	std::unique_ptr<Window> Window::Create(const WindowConfig& config)
	{
		 return std::make_unique<Window>(config);
	}


	void Window::PollEvents()
	{


	}

	SDL_Window* Window::GetNativeWindow() const
	{
		return m_Window;
	}

	bool Window::Init(const WindowConfig& config)
	{
		BJ_LOG("Creating Window " + config.Title + "(" + std::to_string(config.Width) + ", " + std::to_string(config.Height) + ")");

		int status = SDL_Init(SDL_INIT_EVERYTHING);
		BJ_ASSERT(status == 0, "Failed to init SDL! SDL_Error: " + std::string(SDL_GetError()));

		m_Window = SDL_CreateWindow(config.Title.c_str(), SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, config.Width, config.Height,
									SDL_WINDOW_SHOWN);

		BJ_ASSERT(m_Window, "Failed to create window! SDL_Error: " + std::string(SDL_GetError()));

		return true;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
	}

}