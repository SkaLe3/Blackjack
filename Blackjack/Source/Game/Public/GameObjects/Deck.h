#pragma once
#include "World/Entities/GameObject.h"

#include <stack>

class Card;

class Deck : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void PopulateDeck();
	SharedPtr<Card> PullCard();

	void Shuffle();

private:
	std::stack<SharedPtr<Card>> m_Cards;
};