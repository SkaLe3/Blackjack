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
			m_Cards.push_back(newCard);
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
		SharedPtr<Card> topCard = m_Cards.back();
		m_Cards.pop_back();
		return topCard;
	}
	return nullptr;
}

void Deck::Shuffle(bool bWithAnimation)
{
	 std::random_device rd;
	 std::mt19937 g(rd());
	 std::shuffle(m_Cards.begin(), m_Cards.end(), g);

	 for (size_t index = 0; index < m_Cards.size(); index++)
	 {
		 m_Cards[index]->GetTransform().Translation = {index * 0.1, index * 0.1, index * 0.1f};
	 }
	 Animate();
}


void Deck::Animate()
{

}

