#include "GameObjects/Player.h"

#include "GameObjects/ChipStack.h"
#include "GameObjects/CardsHand.h"

void Player::BeginPlay()
{
	Super::BeginPlay();

	auto bet = GetWorld()->SpawnGameObject<ChipStack>();
	bet->AttachToObject(GetSelf());
	m_Bet = bet;

	auto cards = GetWorld()->SpawnGameObject<CardsHand>();
	cards->AttachToObject(GetSelf());
	m_Cards = cards;
}

void Player::PlaceChip(EChipType chip)
{
	if (auto bet = m_Bet.lock())
	{
		bet->CorrectRotation();
		bet->AddChip(chip);
	}
}

void Player::TakeLastChip()
{
	if (auto bet = m_Bet.lock())
	{
		bet->RemoveChip();
	}
}

void Player::TakeCard(SharedPtr<Card> card)
{
	if (auto cards = m_Cards.lock())
	{
		cards->AddCard(card);
	}
}
