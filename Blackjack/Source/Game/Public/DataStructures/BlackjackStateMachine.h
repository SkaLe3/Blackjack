#pragma once
#include <Core/CoreDefines.h>

DECLARE_DELEGATE_NO_PARAMS(BettingStageStarted)
DECLARE_DELEGATE_NO_PARAMS(DealingCardsStageStarted)

DECLARE_DELEGATE_NO_PARAMS(BetPlaced)


struct RoundStateMachine
{
	byte NumberOfPlayers = 0;				// Number of players in game
	byte PlacedBetsCount = 0;				// Number of players who already placed bets

	// Broadcast to players
	BettingStageStarted	OnBettingStageStarted;
	DealingCardsStageStarted OnDealingcardsStageStarted;

	//Broadcast to gamemode
	BetPlaced OnBetPlaced;


	// Constants
	uint32 MaxBet = 50;
	uint32 MinBet = 2;
	float CardsDealingInterval = 1000; // In millis, TODO: make in seconds

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