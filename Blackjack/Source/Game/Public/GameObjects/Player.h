#pragma once
#include "GameObjects/Person.h"

#include "GameObjects/ChipStack.h" // Required for EChipType
#include "DataStructures/PlayerState.h"

#include <Sound/Sound.h>

DECLARE_DELEGATE_NO_PARAMS(GetTurnDelegate);
DECLARE_DELEGATE_ONE_PARAM(ChipActionDelegate, uint32)

class CardsHand;
class Card;
/*
* @class Player
*
* Represents player sitting in front of the game table
*/
class Player : public Person
{
	DECLARE_SUPER(Person)
public:
	Player();
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	/** Balance */
	void SetBalance(int32 balace);
	void AddBalance(int32 amount);
	int32 GetBalance();

	/** Bet */
	virtual void PlaceChip(EChipType chip);
	void TakeLastChip();
	void ConfirmBet();
	int32 GetBetValue();
	void ClearBet();

	/** Turn */
	void CallBlackjack();
	virtual void Hit() override;
	virtual void Stand() override;
	virtual void Bust() override;
	bool TryDoubleDown();
	bool CanDoubleDown();
	void DoubleDown();
	void DealerBust();
	void OverDealer();
	void UnderDealer();
	void Push();
	void Split();	 // Later
	// No insurance

	/** Gameplay */
	void ResetState();
	virtual void AllowToPlay();
	virtual void AllowTurn();
	void ForbidTurn();
	bool IsMyTurn();
	virtual void GameResult(EPlayerResult result) {}
	bool HasFinishedGame();
	void AskForNextRound();
protected:

public:
	GetTurnDelegate OnGotTurn;
	ChipActionDelegate OnChipAction;

protected:
	WeakPtr<ChipStack> m_Bet;
	SharedPtr<PlayerState> m_State;
	int32 m_Balance = 0;

	SharedPtr<Core::SoundBase> m_ConfirmSound;
	SharedPtr<Core::SoundBase> m_ErrorSound;
	SharedPtr<Core::SoundBase> m_LoseSound;




};