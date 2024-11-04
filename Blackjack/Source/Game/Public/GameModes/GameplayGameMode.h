#pragma once
#include <World/Entities/GameMode.h>
#include <Core/Event.h>


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

enum class EPlayerTurn : byte
{
	None = 0, // Currently no one allowed to make turn
	User,
	Bot1,
	Bot2,
	Bot3,
	Reserved
	// In scaling scenario should be expanded
};


class ChipStack;
class Dealer;
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
	//~ Eng Object Interface

	void StartRound();
	void EndRound();
	void NextRound();

	void RestartGame();
	void LeaveGame();

private:
	SharedPtr<Deck> m_Deck;
	SharedPtr<Dealer> m_Dealer;
	SharedPtr<UserPlayer> m_Player;
	SharedPtr<AIPlayer> m_Bot1;
	SharedPtr<AIPlayer> m_Bot2;
};