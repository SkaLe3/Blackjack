#include "GameObjects/Player.h"

#include "GameObjects/ChipStack.h"
#include "GameObjects/CardsHand.h"

void Player::BeginPlay()
{
	Super::BeginPlay();

	auto bet = GetWorld()->SpawnGameObject<ChipStack>();
	bet->AttachToObject(GetSelf());
	bet->GetTransform().Translation.y = 3;
	bet->GetTransform().Translation.z = 10;
	m_Bet = bet;

	auto cards = GetWorld()->SpawnGameObject<CardsHand>();
	cards->AttachToObject(GetSelf());
	cards->GetTransform().Translation.y = 24;
	cards->GetTransform().Translation.z = 0;
	m_Cards = cards;

	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{1, 0, 1, 1}));  // Magenta
	GetBoxComponent()->SetHalfSize({2, 2});
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

bool Player::IsAbleToTakeCard()
{
	if (auto cards = m_Cards.lock())
	{
		return cards->CanAcceptCard();
	}
	return false;
}

void Player::TakeCard(SharedPtr<Card> card)
{
	if (auto cards = m_Cards.lock())
	{
		cards->AcceptCard(card);
	}
}
