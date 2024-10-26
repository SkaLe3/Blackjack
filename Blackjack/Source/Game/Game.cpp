#include <Core/EntryPoint.h>

class Game : public Core::Application
{
public:
	Game(const Core::ApplicationSpecification& appSpecs)
		: Core::Application(appSpecs)
	{

	}
};

Core::Application* Core::CreateApplication(int argc, char** argv)
{
	Core::ApplicationSpecification specs
	{
	.AppConfig {.Name = "Blackjack"},
	.WndConfig {.Title = "Blackjack", .Width = 1000, .Height = 600, .VSync = true}
	};


	Core::Application* game = new Game(specs);
	return game;
}