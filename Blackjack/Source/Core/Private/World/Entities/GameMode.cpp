#include "World/Entities/GameMode.h"
#include "World/Entities/PlayerController.h"
#include "Core/Application.h"

namespace Core
{


	void GameMode::LeaveGame()
	{
		 Application::Get().AskToCloseGame();
	}

}