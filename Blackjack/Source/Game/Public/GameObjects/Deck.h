#pragma once
#include "World/Entities/GameObject.h"

#include <vector>

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

	void Shuffle(bool bWithAnimation = true);
private:
	void Animate();

private:
	std::vector<SharedPtr<Card>> m_Cards;
};