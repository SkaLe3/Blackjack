#include "GameObjects/AIPlayer.h"

#include "GameModes/GameplayGameMode.h"


using namespace Core;

void AIPlayer::BeginPlay()
{
	Super::BeginPlay();

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

	if (m_State->AllowedToTurn)
		TimerManager::Get().StartTimer(1000, [this]() { MakeTurn(); });
}

void AIPlayer::PlaceBet()
{
	int32 minBet = GameState->MinBet;
	int32 maxBet = glm::min(GameState->MaxBet, m_Balance);
	std::uniform_int_distribution<> distrBet(minBet, maxBet);
	m_SelectedChips = SelectChips(distrBet(gen));

	PlaceChipFromSelected();
}

void AIPlayer::MakeTurn()
{
	BJ_LOG_INFO("Make turn %s", GetTag().c_str());
}

std::list<EChipType> AIPlayer::SelectChips(int32 value)
{
	std::list<EChipType> selectedChips;
	for (const auto& [chipType, chipValue] : Chip::ChipsValues)
	{
		while (value >= chipValue)
		{
			selectedChips.push_back(chipType);
			value -= chipValue;
		}
		if (value == 0) break;
	}
	// We don't care if value hasn't become 0
	// The bet would be just lower
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
		std::uniform_int_distribution<>	distrTime(200, 1000);
		m_TimerHandle_PlaceBet = TimerManager::Get().StartTimer(distrTime(gen), [this]() { PlaceChipFromSelected(); });
	}
}


