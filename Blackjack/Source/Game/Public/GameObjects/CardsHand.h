#pragma once
#include <World/Entities/GameObject.h>
#include "GameObjects/Card.h"

#include <Sound/Sound.h>

#include <vector>

class CardsHand : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	CardsHand();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void AcceptCard(SharedPtr<Card> card);
	void AddCard();

	bool CanAcceptCard();

private:
	std::vector<WeakPtr<Card>> m_FirstHand;
	std::vector<WeakPtr<Card>> m_SecondHand;
	SharedPtr<Card> m_LastCard;

	SharedPtr<Core::SoundBase> m_CardSound;

	const float cardOffset = 6.f;
	const float firstCardOffset = cardOffset * 1.5f;
};