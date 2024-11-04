#include "GameObjects/Dealer.h"

#include "GameObjects/CardsHand.h"

void Dealer::BeginPlay()
{
	Super::BeginPlay();

	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 1, 0, 1, 1 }));  // Magenta
	GetBoxComponent()->SetHalfSize({ 2, 2 });

	auto cards = m_Cards.lock();
	cards->GetTransform().Translation.y = 0;
}

void Dealer::PlaceCard(SharedPtr<Card> card)
{
	if (auto cards = m_Cards.lock())
	{
		cards->AcceptCard(card, false);
	}
}
