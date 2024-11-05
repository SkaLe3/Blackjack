#pragma once
#include <Core/CoreDefines.h>
#include "DataStructures/PlayerState.h"

DECLARE_DELEGATE_NO_PARAMS(BettingStageStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(DealingCardsStageStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(PlayerTurnStageStartedDelegate)


DECLARE_DELEGATE_NO_PARAMS(BetPlacedDelegate)
DECLARE_DELEGATE_ONE_PARAM(PlayerHitDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerStandDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerDoubleDownDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerCallBlackjackDelegate, SharedPtr<class Player>)



struct BJGameState
{
	byte NumberOfPlayers = 0;				// Number of players in game
	byte PlacedBetsCount = 0;				// Number of players who already placed bets
	byte MadeTurnsCount = 0;

	// Broadcast to players
	BettingStageStartedDelegate	OnBettingStageStarted;
	DealingCardsStageStartedDelegate OnDealingcardsStageStarted;
	PlayerTurnStageStartedDelegate OnPlayerTurnStageStarted;

	//Broadcast to gamemode
	BetPlacedDelegate OnBetPlaced;
	PlayerHitDelegate OnPlayerHit;
	PlayerStandDelegate	OnPlayerStand;
	PlayerDoubleDownDelegate OnPlayerDoubleDown;
	PlayerCallBlackjackDelegate	 OnPlayerCallBlackjack;

	// Constants
	const uint32 MaxBet = 50;
	const uint32 MinBet = 2;
	const uint32 InitialBalance = 200;
	const float CardsDealingInterval = 600; // In millis, TODO: make in seconds
	const float TimeToStartRound = 3;
};