#pragma once
#include <Core/CoreDefines.h>

DECLARE_DELEGATE_NO_PARAMS(BettingStageStarted)
DECLARE_DELEGATE_NO_PARAMS(DealingCardsStageStarted)
DECLARE_DELEGATE_NO_PARAMS(PlayerTurnStageStarted)


DECLARE_DELEGATE_NO_PARAMS(BetPlaced)


struct BJGameState
{
	byte NumberOfPlayers = 0;				// Number of players in game
	byte PlacedBetsCount = 0;				// Number of players who already placed bets

	// Broadcast to players
	BettingStageStarted	OnBettingStageStarted;
	DealingCardsStageStarted OnDealingcardsStageStarted;
	PlayerTurnStageStarted OnPlayerTurnStageStarted;

	//Broadcast to gamemode
	BetPlaced OnBetPlaced;


	// Constants
	const uint32 MaxBet = 50;
	const uint32 MinBet = 2;
	const uint32 InitialBalance = 200;
	const float CardsDealingInterval = 600; // In millis, TODO: make in seconds
	const float TimeToStartRound = 3;

// 	bool BettingStarted = false;
// 	bool DealingCardsAllStarted = false;
// 	bool DealingCardsPlayers = false;
// 	bool DealingCardDealer = false;
// 	bool CheckForBlackJack = false;
// 	bool PlayerTurn = false;
// 	bool DealerReveal = false;
// 	bool GivingWins = false;
// 	bool Restart = false;
};