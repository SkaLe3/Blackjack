#pragma once
#include <World/Entities/GameMode.h>

#include "DataStructures/BJGameState.h"
#include "DataStructures/PlayerState.h"

#include <Core/Event.h>
#include <Renderer/Texture.h>
#include <Sound/Sound.h>

#include <unordered_map>

enum class ERoundStage : byte
{
	None = 0,
	Registration,
	Betting,
	DealingCards,
	PlayerTurn,
	DealerReveal,
	RoundResult,
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
class Card;
class BlackjackPlayerController;

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
	void NextRound();

	void RestartGame();
	void LeaveGame();

	// Stages
	void RegistrationStage();
	void BettingStage();
	void DealingCardsStage();
	void PlayerTurnStage();
	void DealerRevealStage();
	void RoundResultStage();
	void RestartStage();

	// GameEvents
	void OnDeckReady();	// When deck is created, shuffled and animated
	void OnBetPlaced(); // When players made a bet
	void OnDealCards();	// When Dealing cards started
	void OnPlayersTurn(); // When Players turn stage  started
	void OnDealerStartsReveal();	// When all players finished their turns, need to remove everyone who has blackjack or busted. Dealer reveals card
	void OnCheckResults();
	void OnPlayerHit(SharedPtr<Player> player);	// When player calls Hit
	void OnPlayerStand(SharedPtr<Player> player); // When player calls Stand
	void OnPlayerDoubleDown(SharedPtr<Player> player);	// When player calls DoubleDown
	void OnPlayerCallBlackjack(SharedPtr<Player> player); // When player has blackjack
	void OnPlayerBust(SharedPtr<Player> player);		  // When player called Hit and got busted
	void OnPlayerResultWin(SharedPtr<Player> player);
	void OnPlayerResultLose(SharedPtr<Player> player);
	void OnPlayerResultPush(SharedPtr<Player> player);
	void OnPlayerFinishedGame(SharedPtr<Player> player, EPlayerResult result);	// When player finished game, play sounds and give wins
	void OnDealerRevealed();
	void OnDealerHit();
	void OnDealerStand();
	void OnDealerBust();
	void OnDealerFinishedTurn();
	void OnRestartRound();
	void EndTurnAction();

	SharedPtr<UserPlayer> GetUserPlayer();
	void CycleCardSkin();
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
	bool WaitForReveal();
	bool WaitForFinished();

	void DealCard(SharedPtr<Person> person, bool bFronfaceUp = true);

	void GivePrize(SharedPtr<Player> player, int32 prize);
	void TakeAwayBet(SharedPtr<Player> player, int32 offset);
	// Other
	void ChangeCardsSkin();
;

public:
	RoundStageShiftDelegate OnStageShift;

private:
	// Objects
	SharedPtr<Deck> m_Deck;
	SharedPtr<Dealer> m_Dealer;
	std::vector<SharedPtr<Player>> m_Players;
	std::vector<SharedPtr<Player>> m_ActivePlayers;
	std::vector<SharedPtr<Card>> m_CardsRef;
	std::vector<SharedPtr<ChipStack>> m_WinnerPrizes;
	SharedPtr<Core::Texture> m_SelectedSkinTexture = nullptr;
	std::vector<String> m_SkinsList;
	int32 m_SelectedSkinIndex = 0;


	// Gameplay
	ERoundStage m_RoundStage = ERoundStage::None;
	int32 m_PlayerTurn;
	bool m_ShiftStage = false;
	bool m_bShouldStartRound = false;
	bool m_bDeckReady = false;
	bool m_PlayerMakeTurn = false;
	bool m_DealerMakeTurn = false;
	bool m_ContinueTurn = false;

	SharedPtr<BJGameState> m_GameState;
	SharedPtr<UserPlayer> m_UserPlayer;

	SharedPtr<Core::SoundBase> m_ChipsSound;
};