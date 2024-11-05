#include "GameObjects/AIPlayer.h"

#include "GameModes/GameplayGameMode.h"

#include <SDL2/SDL.h>


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
	//gameState.OnBettingStageStarted.Add(std::bind(&AIPlayer::PlaceBet, this));
}

void AIPlayer::AllowTurn()
{
	Super::AllowTurn();

}

void AIPlayer::PlaceBet()
{
	if (m_State->AllowedToBet && IsMyTurn())
	{
		PlaceChip(EChipType::Blue);
		ConfirmBet();
	}
}


