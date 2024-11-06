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

	void AcceptCard(SharedPtr<Card> card, bool bTurnOver = true);
	void AddCard();
	bool CanAcceptCard();
	int32 CalculateHandValue();
	bool HasAce();
	int32 GetCardCount();

	void Reveal();
	void Clear();
private:
	std::vector<WeakPtr<Card>> m_FirstHand;
	std::vector<WeakPtr<Card>> m_SecondHand; // For split. Curently unused
	SharedPtr<Card> m_LastCard;

	SharedPtr<Core::SoundBase> m_CardTakeSound;
	SharedPtr<Core::SoundBase> m_CardReceiveSound;

	const float cardOffset = 6.f;
	const float firstCardOffset = cardOffset * 1.5f;
};