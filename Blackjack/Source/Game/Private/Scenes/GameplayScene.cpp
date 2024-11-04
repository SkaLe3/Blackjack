#include "Scenes/GameplayScene.h"
#include "GameModes/GameplayGameMode.h"

void GameplayScene::BeginPlay()
{
	m_GameMode = MakeShared<GameplayGameMode>();
	World::BeginPlay();
}

void GameplayScene::OnEvent(Core::Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (event.Ev.key.keysym.sym == SDLK_SPACE)
		{
			std::static_pointer_cast<GameplayGameMode>(m_GameMode)->LeaveGame();

		}
	}
	std::static_pointer_cast<GameplayGameMode>(m_GameMode)->OnEvent(event);
}
