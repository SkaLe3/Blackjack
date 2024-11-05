#pragma once
#include <Core/CoreDefines.h>

DECLARE_DELEGATE_NO_PARAMS(BettingStageStarted)


struct RoundStateMachine
{
	byte NumberOfPlayers = 3;				// Number of players in game
	byte AllowedToPlayPlayersCount = 3;		// Number of players who has balance to play
	byte PlacedBetsCount = 0;				// Number of players who already placed bets




	bool BettingStarted = false;
	bool DealingCardsAllStarted = false;
	bool DealingCardsPlayers = false;
	bool DealingCardDealer = false;
	bool CheckForBlackJack = false;
	bool PlayerTurn = false;
	bool DealerReveal = false;
	bool GivingWins = false;
	bool Restart = false;

	BettingStageStarted	OnBettingStageStarted;
};