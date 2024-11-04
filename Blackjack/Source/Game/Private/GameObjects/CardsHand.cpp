#include "GameObjects/CardsHand.h"

void CardsHand::BeginPlay()
{
	Super::BeginPlay();
	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 0, 1, 1, 1 }));	  // Cyan
	GetBoxComponent()->SetHalfSize({ 2, 2 });
}

void CardsHand::AddCard(SharedPtr<Card> card)
{
	if (card)
	{
		m_FirstHand.emplace_back(card);
		card->AttachToObject(GetSelf());
		card->TurnOver();
		card->SET_BOX_DEBUG_VISIBILITY(true);
		card->SET_BOX_DEBUG_COLOR((glm::vec4{ 1, 1, 0, 1 })); // orange
		card->GetBoxComponent()->SetHalfSize({ 2, 2 });
		card->GetTransform().Translation = {m_FirstHand.size() * 5 - 5, 0, m_FirstHand.size() * 0.1};
	}

}
