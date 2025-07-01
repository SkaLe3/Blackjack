#include "Components/DeckAnimationComponent.h"

#include "GameObjects/Card.h"
#include "Components/CardAnimationComponent.h"

#include <Core/Utils.h>
#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>
#include <Core/TimerManager.h>

using namespace Core;

DeckAnimationComponent::DeckAnimationComponent()
{
	m_CardSound = AssetManager::Get().Load<SoundAsset>("S_DeckCard")->SoundP;
}

void DeckAnimationComponent::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (m_bAnimating) UpdateShuffle(deltaTime);
}

void DeckAnimationComponent::StartShuffleAnimation(const glm::vec2& startPos, float sourceRot, float targetRot, float durationShuffle, float durationCard)
{
	m_StartPos = startPos;
	m_SourceRotation = sourceRot;
	m_TargetRotation = targetRot;
	m_DurationShuffle = durationShuffle;
	m_DurationCard = durationCard;
	m_LastAnimatedIndex = 0;
	m_bAnimating = true;

	m_Deck = std::static_pointer_cast<Deck>(GetOwner().lock());
	for (auto& card : m_Deck->m_Cards)
	{
		glm::vec3 trans = card->GetWorldTransform().Translation;
		m_Positions.emplace_back(trans.x, trans.y);
		glm::vec3& localTrans = card->GetTransform().Translation;
		localTrans.x = -200;
		localTrans.y = 200;
	}

	m_Deck->CardAt(m_Deck->GetCardCount()-1)->GetAnimationComponent()->OnFinishMoveAnim.Add([this](){ OnFinishShuffleAnim.Invoke(); });
}

void DeckAnimationComponent::UpdateShuffle(float deltaTime)
{
	m_Elapsed += deltaTime;
	if (m_Elapsed < m_DurationShuffle)
	{
		float t = m_Elapsed / m_DurationShuffle;
		float f = EaseInOutCubic(t);
		int32 index = f * m_Deck->GetCardCount();
		for (int32 i = m_LastAnimatedIndex; i < index; i++)
		{
			if (SharedPtr<Card> card = m_Deck->CardAt(i))
			{
				card->Move(m_DurationCard, m_StartPos, m_Positions[i], m_SourceRotation, m_TargetRotation);
				TimerManager::Get().StartTimer(m_DurationCard * 1000.f * 0.45f, [this](){ AudioSystem::PlaySound(m_CardSound, 0.4); });
				
				//BJ_LOG_INFO("card: %d", i);
			}
		}
		
		m_LastAnimatedIndex = index;
	}
	else
	{
		for (int32 i = m_LastAnimatedIndex; i < m_Deck->GetCardCount(); i++)
		{
			if (SharedPtr<Card> card = m_Deck->CardAt(i))
			{
				card->Move(m_DurationCard, m_StartPos, m_Positions[i], m_SourceRotation, m_TargetRotation);
				TimerManager::Get().StartTimer(m_DurationCard * 1000.f * 0.45f, [this]() { AudioSystem::PlaySound(m_CardSound, 0.4); });
				//BJ_LOG_INFO("card: %d", i);
			}
		}
		m_Deck->UpdateCardsLocations();
		m_bAnimating = false;
		m_Elapsed = 0.f;	
		m_Deck = nullptr;
		m_Positions.clear();
	}
}
