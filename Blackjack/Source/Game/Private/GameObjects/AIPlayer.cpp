#include "GameObjects/AIPlayer.h"

#include "GameModes/GameplayGameMode.h"

#include <SDL2/SDL.h>

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
	PlaceChip(EChipType::Blue);
	ConfirmBet();

}

void AIPlayer::MakeTurn()
{
	BJ_LOG_INFO("Make turn %s", GetTag().c_str());
}

