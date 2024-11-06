#include <Core/EntryPoint.h>
#include "Scenes/MenuScene.h"
#include "Scenes/GameplayScene.h"

#include <functional>

class Game : public Core::Application
{
public:
	Game(const Core::ApplicationSpecification& appSpecs)
		: Core::Application(appSpecs)
	{

	}
};

namespace Core
{

	Application* CreateApplication(const std::vector<std::string>& arguments)
	{
		uint32 winWidth = 0, winHeight = 0;
		if (arguments.size() > 3)
		{
			for (int i = 0; i < arguments.size(); i++)
			{
				if (arguments[i] == "-window" && arguments.size() < i + 2)
				{
					winWidth = std::stoi(arguments[i+1]);
					winHeight = std::stoi(arguments[i+2]);
				}
			}
		}
		else
		{
			winWidth = 1280;
			winHeight = 720;
		}

		GameplayConfig config;
		std::function<SharedPtr<World>()> startingScene = []() { return static_pointer_cast<World>(MakeShared<MenuScene>()); };
		config.StartingScene = startingScene;
		Core::ApplicationSpecification specs
		{
		.AppConfig {.Name = "Blackjack"},
		.WndConfig {.Title = "Blackjack", .Width = winWidth, .Height = winHeight, .VSync = true},
		.GPConfig = config
		};


		Core::Application* game = new Game(specs);
		return game;
	}
}