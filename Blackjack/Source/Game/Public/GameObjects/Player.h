#pragma once
#include "GameObjects/Person.h"

#include "GameObjects/ChipStack.h" // Required for EChipType
#include "DataStructures/PlayerState.h"

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
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void PlaceChip(EChipType chip);
	void TakeLastChip();
	void ConfirmBet();

	void SetState(SharedPtr<PlayerState> state);

protected:
	WeakPtr<ChipStack> m_Bet;
	WeakPtr<PlayerState> m_State;


};