#pragma once
#include "World/Entities/GameObject.h"

#include <vector>

class Card;
class DeckAnimationComponent;

class Deck : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	Deck();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Destroy() override;
	//~ End Object Interface

	void PopulateDeck(SharedPtr<Core::Texture> skin = nullptr);
	SharedPtr<Card> PullCard();
	void Shuffle();
	uint32 GetCardCount();
	SharedPtr<Card> CardAt(uint32 index);
	std::vector<SharedPtr<Card>> GetCardsRef();

	SharedPtr<DeckAnimationComponent> GetAnimationComponent();
	void Animate(const glm::vec2& startPos, float sourceRot, float targetRot, float durationShuffle, float durationCard);

private:
	void UpdateCardsLocations();

private:
	WeakPtr<DeckAnimationComponent> m_AnimComp;

	std::vector<SharedPtr<Card>> m_Cards;

	friend DeckAnimationComponent;
};