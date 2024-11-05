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
	RoundStateMachine& gameState = static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode())->GetGameState();
	// TODO: Add callbacks
}

void AIPlayer::AllowTurn()
{
	Super::AllowTurn();

	TimerManager::Get().StartTimer(1000, [this](){ PlaceBet(); }, false, true);
}

void AIPlayer::PlaceBet()
{
	if (m_State->AllowedToBet && IsMyTurn())
	{
		PlaceChip(EChipType::Blue);
		ConfirmBet();
	}
}


