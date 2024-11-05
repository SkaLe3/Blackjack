#pragma once
#include "GameObjects/Person.h"

#include "GameObjects/ChipStack.h" // Required for EChipType
#include "DataStructures/PlayerState.h"

#include <Sound/Sound.h>

DECLARE_DELEGATE_NO_PARAMS(GetTurnDelegate);
DECLARE_DELEGATE_ONE_PARAM(ChipActionDelegate, uint32)

class CardsHand;
class Card;
class RoundStateMachine;
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

	virtual void PlaceChip(EChipType chip);
	void TakeLastChip();
	void ConfirmBet();

	void SetState(SharedPtr<PlayerState> state);
	uint32 GetBalance();
	virtual void AllowToPlay();
	virtual void AllowTurn();
	void ForbidTurn();

	bool IsMyTurn();
protected:

public:
	GetTurnDelegate OnGotTurn;
	ChipActionDelegate OnChipAction;

	SharedPtr<RoundStateMachine> GameState;

protected:
	WeakPtr<ChipStack> m_Bet;
	SharedPtr<PlayerState> m_State;
	uint32 m_Balance = 60;


	SharedPtr<Core::SoundBase> m_ConfirmSound;
	SharedPtr<Core::SoundBase> m_ErrorSound;


};