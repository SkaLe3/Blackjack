#include "GameObjects/UserPlayer.h"

#include "GameObjects/Chip.h"
#include "DataStructures/BJGameState.h"
#include "GameObjects/BlackjackPlayerController.h"

#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>
#include <Core/TimerManager.h>

using namespace Core;

void UserPlayer::BeginPlay()
{
	Super::BeginPlay();

	m_WinSound = AssetManager::Get().Load<SoundAsset>("S_Success")->SoundP;
	m_YipeeSound = AssetManager::Get().Load<SoundAsset>("S_Yipee")->SoundP;
	m_FailJingle = AssetManager::Get().Load<SoundAsset>("S_FailJingle")->SoundP;
}


void UserPlayer::GameResult(EPlayerResult result)
{
	Super::GameResult(result);

	switch (result)
	{
	case EPlayerResult::BlackjackWin:
	case EPlayerResult::DefaultWin:
		AudioSystem::PlaySound(m_WinSound);
		AudioSystem::PlaySound(m_YipeeSound);
		break;
	case EPlayerResult::Lose:
		AudioSystem::PlaySound(m_LoseSound, 0.7f);
		AudioSystem::PlaySound(m_FailJingle, 0.7f);
		break;
	case EPlayerResult::Push:
		AudioSystem::PlaySound(m_ErrorSound);
		break;

	}

}

void UserPlayer::AllowTurn()
{
	Super::AllowTurn();

}

void UserPlayer::OnEvent(Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{

		if (m_State && m_State->AllowedToTurn && IsMyTurn() && !HasFinishedGame())
		{
			if (event.Ev.key.keysym.sym == SDLK_h)
			{
				Hit();
			}
			if (event.Ev.key.keysym.sym == SDLK_s)
			{
				Stand();
			}
			if (event.Ev.key.keysym.sym == SDLK_d)
			{
				TryDoubleDown();
			}
		}
		if (m_State && m_State->AskForNextRound)
		{
			if (event.Ev.key.keysym.sym == SDLK_y)
			{
				ContinueToNextRound();
			}
			if (event.Ev.key.keysym.sym == SDLK_n)
			{
				QuitGame();
			}
		}
	}

}

bool UserPlayer::CanBet()
{
	return	m_State && m_State->AllowedToBet && IsMyTurn() && !HasFinishedGame();
}

bool UserPlayer::CanMakeTurn()
{
	return m_State && m_State->AllowedToTurn && IsMyTurn() && !HasFinishedGame();
}

bool UserPlayer::ContinueToNextRound()
{
	SharedPtr<BlackjackPlayerController> pc = static_pointer_cast<BlackjackPlayerController>(GetWorld()->GetPlayerController());
	pc->OnContinueToNextRound();
	if (GameState)
	{
		if (GameState->MinBet < m_Balance)
		{
			BJ_LOG_INFO("======NEW ROUND STARTED=====");
			GameState->OnNextRound.Broadcast();
			return true;
		}
		else
		{
			BJ_LOG_INFO("NOT ENOUGH BALANCE TO START NEW ROUND");
			return false;
		}
	}
	return false;
}

bool UserPlayer::QuitGame()
{
	BJ_LOG_INFO("LEAVING GAME");
	if (GameState)
	{
		GameState->OnLeaveGame.Broadcast();
	}
	return true;
}

void UserPlayer::AskForNextRound()
{
	Player::AskForNextRound();
	SharedPtr<BlackjackPlayerController> pc = static_pointer_cast<BlackjackPlayerController>(GetWorld()->GetPlayerController());
	TimerManager::Get().StartTimer(4000.f, TIMER_ACTION(pc->OnAskForNextRound(m_ResultType)));
}

