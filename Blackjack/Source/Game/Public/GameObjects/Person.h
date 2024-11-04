#pragma once
#include <World/Entities/GameObject.h>

class CardsHand;
class Card;

/*
* @class Player
*
* Represents person sitting in front of the game table (may be dealer or player)
*/
class Person : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	bool IsAbleToTakeCard();
	void TakeCard(SharedPtr<Card> card);

	void ClearHand();

protected:
	WeakPtr<CardsHand> m_Cards;
};