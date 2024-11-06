#pragma once
#include "Core/Application.h"
#include "IO/Log.h"

#include <vector>
#include <SDL2/SDL_main.h> // only include this one in the source file with main()!

extern Core::Application* Core::CreateApplication(const std::vector<std::string>& arguments);

namespace Core
{
	int Main(const std::vector<std::string>& arguments)
	{
		Core::Application* app = Core::CreateApplication(arguments);
		app->Run();
		delete app;

		return 0;
	}
}

int main(int argc, char** argv)
{
	std::vector<std::string> arguments;
	for (int idx = 1; idx < argc; idx++)
	{
		arguments.emplace_back(argv[idx]);
	}
	return Core::Main(arguments);
};