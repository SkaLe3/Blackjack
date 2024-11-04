#pragma once
#include <World/Entities/GameObject.h>

#include "GameObjects/ChipStack.h" // Required for EChipType


class CardsHand;
class Card;
/*
* @class Player
*
* Represents player sitting in front of the game table
*/
class Player : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void PlaceChip(EChipType chip);
	void TakeLastChip();

	bool IsAbleToTakeCard();
	void TakeCard(SharedPtr<Card> card);

private:
	WeakPtr<ChipStack> m_Bet;
	WeakPtr<CardsHand> m_Cards;
};