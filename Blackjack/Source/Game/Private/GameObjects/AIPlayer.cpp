#include "GameObjects/AIPlayer.h"

#include "GameModes/GameplayGameMode.h"


#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

using namespace Core;

void AIPlayer::BeginPlay()
{
	Super::BeginPlay();
	// TODO: Add AI component which will make all choices

	m_WinSound = AssetManager::Get().Load<SoundAsset>("S_Tada")->SoundP;
}

void AIPlayer::Tick(float deltaTime)
{

}

void AIPlayer::AllowToPlay()
{
	Super::AllowToPlay();
	// TODO: Add callbacks
}

void AIPlayer::AllowTurn()
{
	Super::AllowTurn();
	if (m_State->AllowedToBet)
		TimerManager::Get().StartTimer(1000, [this]() { PlaceBet(); });

	if (m_State->FinishedGame)
	{
		return;
	}

	if (m_State->AllowedToTurn)
		TimerManager::Get().StartTimer(2000, [this]() { MakeTurn(); });
}

void AIPlayer::GameResult(EPlayerResult result)
{
	Super::GameResult(result);

	switch (result)
	{
	case EPlayerResult::Lose:
		AudioSystem::PlaySound(m_LoseSound);
		break;
	case EPlayerResult::BlackjackWin:
	case EPlayerResult::DefaultWin:
		AudioSystem::PlaySound(m_WinSound);
		break;
	case EPlayerResult::Push:
		AudioSystem::PlayMusic(m_ErrorSound);
		break;
	}
}

void AIPlayer::PlaceBet()
{
	int32 minBet = GameState->MinBet;
	int32 maxBet = glm::min(GameState->MaxBet, m_Balance);
	std::uniform_int_distribution<> distrBet(minBet, maxBet);
	int32 bet = distrBet(gen);
	m_SelectedChips = SelectChips(bet);
	BJ_LOG_INFO("%s: Generated bet: %d", GetTag().c_str(), bet);

	PlaceChipFromSelected();
}

void AIPlayer::MakeTurn()
{
	BJ_LOG_INFO("Make turn %s", GetTag().c_str());

	Hit();


}

std::list<EChipType> AIPlayer::SelectChips(int32 value)
{
	std::list<EChipType> selectedChips;

	std::uniform_int_distribution<> distr(0, 1); // Decide to skip or not

	for (const auto& [chipType, chipValue] : Chip::ChipsValues)
	{
		while (value >= chipValue)
		{
			if (distr(gen) == 0 || chipValue == 1)
			{
				selectedChips.push_back(chipType);
				value -= chipValue;
			}
		}
		if (value == 0) break;
	}
	if (value != 0)
	{
		// This should never happen
		selectedChips.pop_back();
	}
	return selectedChips;
}

void AIPlayer::PlaceChipFromSelected()
{
	EChipType chip = m_SelectedChips.front();
	m_SelectedChips.pop_front();

	PlaceChip(chip);

	if (m_SelectedChips.empty())
	{
		ConfirmBet();
	}
	else
	{
		std::uniform_int_distribution<>	distrTime(400, 1000);
		m_TimerHandle_PlaceBet = TimerManager::Get().StartTimer(distrTime(gen), [this]() { PlaceChipFromSelected(); });
	}
}


