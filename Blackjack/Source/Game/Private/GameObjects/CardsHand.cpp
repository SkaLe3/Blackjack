#include "GameObjects/CardsHand.h"

#include "Components/CardAnimationComponent.h"

#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>
#include <Core/TimerManager.h>

using namespace Core;

CardsHand::CardsHand()
{
	m_CardTakeSound = AssetManager::Get().Load<SoundAsset>("S_TakeCard")->SoundP;
	m_CardReceiveSound = AssetManager::Get().Load<SoundAsset>("S_DeckCard")->SoundP;
}

void CardsHand::BeginPlay()
{
	Super::BeginPlay();
	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 0, 1, 1, 1 }));	  // Cyan
	GetBoxComponent()->SetHalfSize({ 2, 2 });


}

void CardsHand::AcceptCard(SharedPtr<Card> card, bool m_bTurnOver /*= true*/)
{
	if (card && CanAcceptCard())
	{
		m_FirstHand.emplace_back(card);

		glm::vec3 inDeckPosition;
		glm::vec3 inHandPosition;
		float inDeckRotation = 0;
		float inHandRotation = 0;

		// Kinda bad workaround but its ok
		Transform inDeckTransform = card->GetWorldTransform();
		card->DetachFromObject();
		card->AttachToObject(GetSelf());
		card->GetTransform() = Transform();
		card->GetTransform().Translation.x += m_FirstHand.size() * cardOffset - firstCardOffset;
		Transform inHandTransform = card->GetWorldTransform();
		card->DetachFromObject();

		inDeckPosition = inDeckTransform.Translation;
		inHandPosition = inHandTransform.Translation;
		inDeckRotation = inDeckTransform.Rotation.z;
		inHandRotation = inHandTransform.Rotation.z;
		card->GetTransform().Translation = inDeckPosition;
		card->GetTransform().Translation.z = 100;

		m_LastCard = card;
		if (m_bTurnOver)
		{
			card->TurnOver(1, 1);
		}
		const float moveDuration = 1.0f;
		card->Move(moveDuration, inDeckPosition, inHandPosition, glm::degrees(inDeckRotation), 180 + glm::degrees(inHandRotation), false);
		card->GetAnimationComponent()->OnFinishMoveAnim.Add(std::bind(&CardsHand::AddCard, this));
		AudioSystem::PlaySound(m_CardTakeSound, 0.2f);
		TimerManager::Get().StartTimer(moveDuration * 1000.f * 0.45f, [this]() { AudioSystem::PlaySound(m_CardReceiveSound, 0.2f); });


	}
}

void CardsHand::AddCard()
{
	if (!m_LastCard)
		return;

	m_LastCard->AttachToObject(GetSelf());

	float xPos = m_FirstHand.size() * cardOffset - firstCardOffset;
	float zPos = m_FirstHand.size() * 0.1f;
	m_LastCard->GetTransform().Translation = { xPos, 0, zPos };
	m_LastCard->GetTransform().Rotation.z = glm::radians(180.0f);
	m_LastCard = nullptr;
}

bool CardsHand::CanAcceptCard()
{
	return m_LastCard == nullptr;
}

int32 CardsHand::CalculateHandValue()
{
	int32 totalValue = 0;
	int aceCount = 0;

	for (const auto& weakCard : m_FirstHand)
	{
		auto card = weakCard.lock();
		if (card)
		{
			if (card->GetFace() == ECardFace::Back)
				continue;
			int32 cardValue = card->GetValue();
			totalValue += cardValue;

			// Count the number of Aces separately
			if (card->GetRank() == ECardRank::Ace)
			{
				++aceCount;
			}
		}
	}
	// Adjust Aces from 11 to 1 if totalValue exceeds 21
	while (totalValue > 21 && aceCount > 0)
	{
		totalValue -= 10;
		--aceCount;
	}
	return totalValue;
}

bool CardsHand::HasAce()
{
	for (const auto& weakCard : m_FirstHand)
	{
		auto card = weakCard.lock();
		if (card)
		{
			if (card->GetFace() == ECardFace::Back)
			continue;
			if (card->GetRank() == ECardRank::Ace)
			{
				return true;
			}
		}
	}  
	return false;
}

int32 CardsHand::GetCardCount()
{
	 return m_FirstHand.size();
}

void CardsHand::Reveal()
{
	for (const auto& weakCard : m_FirstHand)
	{
		auto card = weakCard.lock();
		if (card)
		{
			if (card->GetFace() == ECardFace::Back)
			{
				card->TurnOver(0.6f, 0);
			}

		}
	}
}

void CardsHand::Clear()
{
	for (auto& card : m_FirstHand)
	{
		if (auto sharedCard = card.lock())
		{
			sharedCard->Destroy();
		}
	}
	for (auto& card : m_SecondHand)
	{
		if (auto sharedCard = card.lock())
		{
			sharedCard->Destroy();
		}
	}
	m_FirstHand.clear();
	m_SecondHand.clear();
	if (m_LastCard)
		m_LastCard->Destroy();
	m_LastCard = nullptr;
}
