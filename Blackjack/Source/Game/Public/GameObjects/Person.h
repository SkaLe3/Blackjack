#pragma once
#include <World/Entities/GameObject.h>

class CardsHand;
class Card;
class BJGameState;

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

	virtual void Hit() {}
	virtual void Stand() {}
	virtual void Bust() {}

	int32 GetHandValue();
	bool IsAbleToTakeCard();
	void TakeCard(SharedPtr<Card> card);
	/** Alternative to TakeCard() function, to place card front face down*/
	void PlaceCard(SharedPtr<Card> card);

	void ClearHand();

	SharedPtr<CardsHand> GetCardsHand();

public:
	SharedPtr<BJGameState> GameState;

protected:
	WeakPtr<CardsHand> m_Cards;
};