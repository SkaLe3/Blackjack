#pragma once
#include <Core/CoreDefines.h>
#include "DataStructures/PlayerState.h"

DECLARE_DELEGATE_NO_PARAMS(BettingStageStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(DealingCardsStageStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(PlayerTurnStageStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(DealerRevealStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(RoundResultStageStartedDelegate)
DECLARE_DELEGATE_NO_PARAMS(RestartRoundStageStartedDelegate)


DECLARE_DELEGATE_NO_PARAMS(BetPlacedDelegate)
DECLARE_DELEGATE_ONE_PARAM(PlayerHitDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerStandDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerDoubleDownDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerCallBlackjackDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerBustDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerResultWinDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerResultLoseDelegate, SharedPtr<class Player>)
DECLARE_DELEGATE_ONE_PARAM(PlayerResultPushDelegate, SharedPtr<class Player>)

DECLARE_DELEGATE_NO_PARAMS(DealerRevealedDelegate)
DECLARE_DELEGATE_NO_PARAMS(DealerHitDelegate)
DECLARE_DELEGATE_NO_PARAMS(DealerStandDelegate)
DECLARE_DELEGATE_NO_PARAMS(DealerBustDelegate)

DECLARE_DELEGATE_NO_PARAMS(StartNextRoundDelegate)
DECLARE_DELEGATE_NO_PARAMS(LeaveGameDelegate)



struct BJGameState
{
	byte NumberOfRegisteredPlayers = 0;				// Number of players in game
	byte NumberOfFhinishedPlayers = 0;
	byte PlacedBetsCount = 0;				// Number of players who already placed bets
	byte MadeTurnsCount = 0;
	int32 CurrentDealerHandValue = 0;
	bool bDealerFinishedTurn = false;

	// Broadcast to players
	BettingStageStartedDelegate	OnBettingStageStarted;
	DealingCardsStageStartedDelegate OnDealingcardsStageStarted;
	PlayerTurnStageStartedDelegate OnPlayerTurnStageStarted;
	DealerRevealStartedDelegate OnDealerRevealStageStarted;
	RoundResultStageStartedDelegate OnRoundResultStageStarted;
	RestartRoundStageStartedDelegate OnRestartRoundStageStarted;

	//Broadcast to gamemode
	BetPlacedDelegate OnBetPlaced;
	PlayerHitDelegate OnPlayerHit;
	PlayerStandDelegate	OnPlayerStand;
	PlayerDoubleDownDelegate OnPlayerDoubleDown;
	PlayerCallBlackjackDelegate	 OnPlayerCallBlackjack;
	PlayerBustDelegate OnPlayerBust;
	PlayerResultWinDelegate OnPlayerResultWin;
	PlayerResultLoseDelegate OnPlayerResultLose;
	PlayerResultPushDelegate OnPlayerResultPush;

	DealerRevealedDelegate OnDealerRevealed;
	DealerHitDelegate OnDealerHit;
	DealerStandDelegate OnDealerStand;
	DealerBustDelegate OnDealerBust;

	StartNextRoundDelegate OnNextRound;
	LeaveGameDelegate OnLeaveGame;

	// Constants		   // TODO: Move to game settings
	const int32 MaxBet = 50;
	const int32 MinBet = 2;
	const int32 InitialBalance = 80;
	const float CardsDealingInterval = 600; // In millis, TODO: make in seconds
	const float TimeToStartRound = 3;
};