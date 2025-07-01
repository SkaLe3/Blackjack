#include "GameObjects/Dealer.h"

#include "GameObjects/CardsHand.h"
#include "DataStructures/BJGameState.h"

#include <Core/TimerManager.h>
#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

using namespace Core;

Dealer::Dealer()
{
	m_ConfirmSound = AssetManager::Get().Load<SoundAsset>("S_Confirm")->SoundP;
}

void Dealer::BeginPlay()
{
	Super::BeginPlay();

	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 1, 0, 1, 1 }));  // Magenta
	GetBoxComponent()->SetHalfSize({ 2, 2 });

	auto cards = m_Cards.lock();
	cards->GetTransform().Translation.y = 0;
}

void Dealer::Tick(float deltaTime)
{
	 Super::Tick(deltaTime);
	 if (m_bRevealed)
	 {
		 m_bRevealed = false;
		 GameState->OnDealerRevealed.Broadcast();
	 }
}

void Dealer::Hit()
{
	Super::Hit();
	GameState->OnDealerHit.Broadcast();

}

void Dealer::Stand()
{
	Super::Stand();
	GameState->OnDealerStand.Broadcast();
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Dealer::Bust()
{
	Super::Bust();
	GameState->OnDealerBust.Broadcast();
}

void Dealer::StartReveal()
{
	if (const auto& hand = m_Cards.lock())
	{
		hand->Reveal();
	}
	TimerManager::Get().StartTimer(1500.f, [this]() { m_bRevealed = true; });
}

void Dealer::MakeTurn()
{
	BJ_LOG_INFO("Dealer makes turn");
	if (auto hand = m_Cards.lock())
	{
		int32 handValue = hand->CalculateHandValue();
		BJ_LOG_INFO("Deler hand %d", handValue);
		if (handValue <= 16)
		{
			Hit();
			return;
		}
		if (handValue <= 21)
		{
			Stand();
			return;
		}
		Bust();
	}
}

