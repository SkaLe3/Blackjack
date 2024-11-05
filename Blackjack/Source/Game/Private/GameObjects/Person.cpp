#include "GameObjects/Person.h"
#include "GameObjects/CardsHand.h"


bool Person::IsAbleToTakeCard()
{
	if (auto cards = m_Cards.lock())
	{
		return cards->CanAcceptCard();
	}
	return false;
}

void Person::TakeCard(SharedPtr<Card> card)
{
	if (auto cards = m_Cards.lock())
	{
		cards->AcceptCard(card);
	}
}

void Person::PlaceCard(SharedPtr<Card> card)
{
	if (auto cards = m_Cards.lock())
	{
		cards->AcceptCard(card, false);
	}
}

void Person::ClearHand()
{
	 m_Cards.lock()->Clear();
}

void Person::BeginPlay()
{
   Super::BeginPlay();

   auto cards = GetWorld()->SpawnGameObject<CardsHand>();
   cards->AttachToObject(GetSelf());
   cards->GetTransform().Translation.y = 24;
   cards->GetTransform().Translation.z = 0;
   m_Cards = cards;
}
