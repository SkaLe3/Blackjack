#include "GameObjects/Deck.h" 
#include "GameObjects/Card.h"
#include "Assets/CardTextureAtlas.h"
#include "Components/DeckAnimationComponent.h"

#include <vector>
#include <algorithm>
#include <random>

using namespace Core;

Deck::Deck()
{
	m_AnimComp = CreateComponent<DeckAnimationComponent>();
}

void Deck::BeginPlay()
{
	Super::BeginPlay();
	GetAnimationComponent()->SetOwner(GetSelf());
	SetTag("deck");

}

void Deck::PopulateDeck()
{
	SharedPtr<TextureAtlas> atlas = MakeShared<CardTextureAtlas>();

	const char* suits[] = { "spades", "diamonds", "clubs", "hearts" };
	const char* ranks[] = { "2","3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	const ECardRank e_ranks[] = {
	ECardRank::Two,
	ECardRank::Three,
	ECardRank::Four,
	ECardRank::Five,
	ECardRank::Six,
	ECardRank::Seven,
	ECardRank::Eight,
	ECardRank::Nine,
	ECardRank::Ten,
	ECardRank::Jack,
	ECardRank::Queen,
	ECardRank::King,
	ECardRank::Ace
	};

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
			newCard->AssignRank(e_ranks[j]);

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

void Deck::Shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Cards.begin(), m_Cards.end(), g);

	UpdateCardsLocations();
}

uint32 Deck::GetCardCount()
{
	return m_Cards.size();
}

SharedPtr<Card> Deck::CardAt(uint32 index)
{
	if (index < m_Cards.size())
		return m_Cards[index];
	return nullptr;
}

SharedPtr<DeckAnimationComponent> Deck::GetAnimationComponent()
{
	return m_AnimComp.lock();
}


void Deck::Animate(const glm::vec2& startPos, float sourceRot, float targetRot, float durationShuffle, float durationCard)
{
	GetAnimationComponent()->StartShuffleAnimation(startPos, sourceRot, targetRot, durationShuffle, durationCard);
}

void Deck::UpdateCardsLocations()
{
	for (size_t index = 0; index < m_Cards.size(); index++)
	{
		m_Cards[index]->GetTransform().Translation = { index * 0.1, index * 0.1, index * 0.1f };
	}
}

