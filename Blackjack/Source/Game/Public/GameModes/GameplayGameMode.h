#pragma once
#include <World/Entities/GameMode.h>

#include "DataStructures/BlackjackStateMachine.h"
#include "DataStructures/PlayerState.h"

#include <Core/Event.h>

#include <unordered_map>




enum class ERoundStage : byte
{
   Betting = 0,
   DealingCardsAll,
   DealingCardsPlayers,
   DealingCardDealer,
   CheckForBlackJack,
   PlayerTurn,
   DealerReveal,
   GivingWins,
   Restart

};

DECLARE_DELEGATE_ONE_PARAM(RoundStageShiftDelegate, ERoundStage);

class ChipStack;
class Dealer;
class Player;
class UserPlayer;
class AIPlayer;
class Deck;

class GameplayGameMode : public Core::GameMode
{
	DECLARE_SUPER(Core::GameMode)
public:
	GameplayGameMode() = default;
	~GameplayGameMode() = default;

	void OnEvent(Core::Event& event);

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	//~ Eng Object Interface

	void StartRound();
	void EndRound();
	void RoundResult();
	void NextRound();

	void RestartGame();
	void LeaveGame();


	// GameEvents
	void BetPlacedEvent();
	// TODO: move some functions to private section
private:
	void StartBetting();
	bool WaitForBets();

public:
	RoundStageShiftDelegate OnStageShift;

private:
	// Objects
	SharedPtr<Deck> m_Deck;
	SharedPtr<Dealer> m_Dealer;
	std::vector<SharedPtr<Player>> m_Players;
	std::vector<SharedPtr<PlayerState>> m_PStates;

	// Constants
	float m_MaxBet = 50;
	float m_MinBet = 1;

	// Gameplay
	ERoundStage m_RoundStage;
	byte m_PlayerTurn;
	//std::vector<ERoundStage> m_Stages;
	bool m_ShiftStage = false;

	RoundStateMachine m_GameState;

};