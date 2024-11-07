#include "Scenes/MenuScene.h"
#include "GameModes/MenuGameMode.h"
#include "GameObjects/MenuPlayerController.h"

using namespace Core;


void MenuScene::BeginPlay()
{
	m_GameMode = MakeShared<MenuGameMode>();
	m_PlayerController = MakeShared<MenuPlayerController>();
	World::BeginPlay();


}

void MenuScene::OnEvent(Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_SPACE)
		{
			std::static_pointer_cast<MenuGameMode>(m_GameMode)->StartGame();
		}
	}
	std::static_pointer_cast<MenuGameMode>(m_GameMode)->OnEvent(event);
}
