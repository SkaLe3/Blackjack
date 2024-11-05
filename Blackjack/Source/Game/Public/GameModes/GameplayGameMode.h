#pragma once
#include <World/Entities/GameMode.h>

#include "DataStructures/BJGameState.h"
#include "DataStructures/PlayerState.h"

#include <Core/Event.h>

#include <unordered_map>




enum class ERoundStage : byte
{
	None = 0,
	Registration,
	Betting,
	DealingCards,
	PlayerTurn,
	DealerReveal,
	GivingWins,
	Restart

};

DECLARE_DELEGATE_ONE_PARAM(RoundStageShiftDelegate, ERoundStage);

class ChipStack;
class Person;
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
	void OnDeckReady();
	void OnBetPlaced();
	void OnDealCards();
	void OnRemoveFinished();
	void OnPlayerHit(SharedPtr<Player> player);
	void OnPlayerStand(SharedPtr<Player> player);
	void OnPlayerDoubleDown(SharedPtr<Player> player);
	void OnPlayerCallBlackjack(SharedPtr<Player> player);
	void OnPlayerFinishedGame(SharedPtr<Player> player, EPlayerResult result);
	void EndTurnAction();

	// TODO: move some functions to private section
private:
	void SubscribeForEvents();
	void ShiftStage();
	void OnNewStage();
	void ShiftTurn();
	void OnNewTurn();
	void MakeTurn();
	void ResetTurn();
	bool WaitForBets();
	bool WaitForTurns();

	void DealCard(SharedPtr<Person> person, bool bFronfaceUp = true);

public:
	RoundStageShiftDelegate OnStageShift;

private:
	// Objects
	SharedPtr<Deck> m_Deck;
	SharedPtr<Dealer> m_Dealer;
	std::vector<SharedPtr<Player>> m_Players;
	std::vector<SharedPtr<Player>> m_ActivePlayers;
	std::vector<SharedPtr<Player>> m_FinishedPlayers;



	// Gameplay
	ERoundStage m_RoundStage = ERoundStage::None;
	int32 m_PlayerTurn;
	//std::vector<ERoundStage> m_Stages;
	bool m_ShiftStage = false;
	bool m_bShouldStartRound = false;
	bool m_bDeckReady = false;
	bool m_MakeTurn = false;

	SharedPtr<BJGameState> m_GameState;
	

};