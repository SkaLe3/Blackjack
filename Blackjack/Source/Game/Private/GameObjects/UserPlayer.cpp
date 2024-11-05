#include "GameObjects/UserPlayer.h"

#include "GameObjects/Chip.h"


#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

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
		AudioSystem::PlaySound(m_LoseSound);
		AudioSystem::PlaySound(m_FailJingle);
		break;
	case EPlayerResult::Push:
		AudioSystem::PlayMusic(m_ErrorSound);
		break;

	}

}

void UserPlayer::OnEvent(Event& event)
{
	if (event.Ev.type == SDL_KEYDOWN)
	{
		if (m_State->AllowedToBet && IsMyTurn() && !HasFinishedGame())
		{

			if (event.Ev.key.keysym.sym == SDLK_1)
			{
				PlaceChip(EChipType::White);
			}
			if (event.Ev.key.keysym.sym == SDLK_2)
			{
				PlaceChip(EChipType::Red);
			}
			if (event.Ev.key.keysym.sym == SDLK_3)
			{
				PlaceChip(EChipType::Blue);
			}
			if (event.Ev.key.keysym.sym == SDLK_4)
			{
				PlaceChip(EChipType::Gray);
			}
			if (event.Ev.key.keysym.sym == SDLK_5)
			{
				PlaceChip(EChipType::Green);
			}
			if (event.Ev.key.keysym.sym == SDLK_6)
			{
				PlaceChip(EChipType::Orange);
			}
			if (event.Ev.key.keysym.sym == SDLK_MINUS)
			{
				TakeLastChip();
			}
			if (event.Ev.key.keysym.sym == SDLK_EQUALS)
			{
				ConfirmBet();
			}
		}
		if (m_State->AllowedToTurn && IsMyTurn() && !HasFinishedGame())
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
				DoubleDown();
			}
		}
	}



	// TODO: Move to widget
	static EChipType chipType;
}
