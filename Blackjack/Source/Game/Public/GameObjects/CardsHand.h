#pragma once
#include <World/Entities/GameObject.h>
#include "GameObjects/Card.h"

#include <vector>

class CardsHand : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void AddCard(SharedPtr<Card> card);
	

private:
	std::vector<WeakPtr<Card>> m_FirstHand;
	std::vector<WeakPtr<Card>> m_SecondHand;


};