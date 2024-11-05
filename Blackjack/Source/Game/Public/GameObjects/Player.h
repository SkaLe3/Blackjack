#pragma once
#include "GameObjects/Person.h"

#include "GameObjects/ChipStack.h" // Required for EChipType
#include "DataStructures/PlayerState.h"

#include <Sound/Sound.h>

DECLARE_DELEGATE_NO_PARAMS(GetTurnDelegate);

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

	void PlaceChip(EChipType chip);
	void TakeLastChip();
	void ConfirmBet();

	void SetState(SharedPtr<PlayerState> state);
	bool HasBalance();
	virtual void AllowToPlay();
	virtual void AllowTurn();
	void ForbidTurn();

	bool IsMyTurn();
protected:

public:
	GetTurnDelegate OnGotTurn;

protected:
	WeakPtr<ChipStack> m_Bet;
	SharedPtr<PlayerState> m_State;


	SharedPtr<Core::SoundBase> m_ConfirmSound;


};