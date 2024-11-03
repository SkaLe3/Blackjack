#pragma once
#include "World/Entities/GameObject.h"

#include <queue>

class Card;

class Deck : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void PopulateDeck();

private:
	std::queue<SharedPtr<Card>> m_Cards;
};