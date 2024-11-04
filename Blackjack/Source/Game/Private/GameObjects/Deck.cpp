#include "GameObjects/Deck.h" 
#include "GameObjects/Card.h"
#include "Assets/CardTextureAtlas.h"

#include <vector>
#include <algorithm>
#include <random>

using namespace Core;

void Deck::BeginPlay()
{
	Super::BeginPlay();

	SetTag("deck");

}

void Deck::PopulateDeck()
{
	SharedPtr<TextureAtlas> atlas = MakeShared<CardTextureAtlas>();

	const char* suits[] = { "spades", "diamonds", "clubs", "hearts" };
	const char* ranks[] = { "2","3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			SharedPtr<Card> newCard = GetWorld()->SpawnGameObject<Card>();
			m_Cards.push(newCard);
			newCard->AttachToObject(GetSelf());
			float index = i * 13 + j;
			newCard->GetTransform().Translation = { index * 0.1, index * 0.1, index };
			auto spriteComp = newCard->GetSpriteComponent();
			spriteComp->SetAtlas(atlas);
			newCard->AssignFrontFace(String(ranks[j]) + '_' + suits[i]);
			newCard->AssignBackFace("back");
			newCard->SetInitialState(ECardFace::Back);

		}
	}

}

SharedPtr<Card> Deck::PullCard()
{
	if (!m_Cards.empty())
	{
		SharedPtr<Card> topCard = m_Cards.top();
		m_Cards.pop();
		return topCard;
	}
	return nullptr;
}

void Deck::Shuffle()
{
	// Consider using a vector for the deck to improve performance.
	// Although this approach is inefficient, it only runs once per round and is acceptable in this context.

	 std::vector<SharedPtr<Card>> cards;
	 while (!m_Cards.empty())
	 {
		 cards.push_back(m_Cards.top());
		 m_Cards.pop();
	 }

	 std::random_device rd;
	 std::mt19937 g(rd());
	 std::shuffle(cards.begin(), cards.end(), g);

	 for (size_t index = 0; index < cards.size(); index++)
	 {
		 m_Cards.push(cards[index]);
		 cards[index]->GetTransform().Translation = {index * 0.1, index * 0.1, index * 0.1f};
	 }
}

