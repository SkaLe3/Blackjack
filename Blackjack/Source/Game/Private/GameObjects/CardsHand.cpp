#include "GameObjects/CardsHand.h"

#include "Components/CardAnimationComponent.h"

#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

using namespace Core;

CardsHand::CardsHand()
{
	m_CardSound = AssetManager::Get().Load<SoundAsset>("S_TakeCard")->SoundP;
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
		card->GetTransform().Translation.z = 100;
		Transform inHandTransform = card->GetWorldTransform();
		card->DetachFromObject();

		inDeckPosition = inDeckTransform.Translation;
		inHandPosition = inHandTransform.Translation;
		inDeckRotation = inDeckTransform.Rotation.z;
		inHandRotation = inHandTransform.Rotation.z;

		m_LastCard = card;
		if (m_bTurnOver)
		{
			card->TurnOver(1, 1);
		}
		card->Move(1.f, inDeckPosition, inHandPosition, glm::degrees(inDeckRotation), 180 + glm::degrees(inHandRotation), false);
		card->GetAnimationComponent()->OnFinishMoveAnim.Add(std::bind(&CardsHand::AddCard, this));
		AudioSystem::PlaySound(m_CardSound, 0.2f);


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
