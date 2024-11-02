#include "GameObjects/Deck.h" 



void Deck::BeginPlay()
{
	Super::BeginPlay();

	SetTag("deck");

	GetTransform().Translation = {-50, 20, 0};
}

