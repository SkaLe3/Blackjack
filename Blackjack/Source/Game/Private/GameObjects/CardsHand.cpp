#include "GameObjects/CardsHand.h"

void CardsHand::AddCard(SharedPtr<Card> card)
{
	if (card)
	{
		m_FirstHand.emplace_back(card);
		card->AttachToObject(GetSelf());
	}

}
