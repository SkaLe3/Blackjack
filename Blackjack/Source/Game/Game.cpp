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

	Application* CreateApplication(int argc, char** argv)
	{
		GameplayConfig config;
		std::function<SharedPtr<World>()> startingScene = []() { return static_pointer_cast<World>(MakeShared<MenuScene>()); };
		config.StartingScene = startingScene;
		Core::ApplicationSpecification specs
		{
		.AppConfig {.Name = "Blackjack"},
		.WndConfig {.Title = "Blackjack", .Width = 1280, .Height = 720, .VSync = true},
		.GPConfig = config
		};


		Core::Application* game = new Game(specs);
		return game;
	}
}