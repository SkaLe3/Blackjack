#include "GameObjects/Deck.h" 
#include "GameObjects/Card.h"
#include "Assets/CardTextureAtlas.h"

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
			newCard->AssignFrontFace(String(ranks[j]) + '_' + suits[i])	;
			newCard->AssignBackFace("back");
			newCard->SetInitialState(CardFace::Back);

		}
	}

}

