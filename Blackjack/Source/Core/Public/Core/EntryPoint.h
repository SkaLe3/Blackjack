#pragma once
#include "Core/Application.h"
#include "IO/Log.h"

#include <SDL2/SDL_main.h> // only include this one in the source file with main()!

extern Core::Application* Core::CreateApplication(int argc, char** argv);

namespace Core
{
	int Main(int argc, char** argv)
	{
		Core::Application* app = Core::CreateApplication(argc, argv);
		app->Run();
		delete app;

		return 0;
	}
}

int main(int argc, char** argv)
{
	return Core::Main(argc, argv);
};