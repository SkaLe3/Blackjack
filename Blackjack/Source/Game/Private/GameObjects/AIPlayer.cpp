#include "GameObjects/AIPlayer.h"

#include "GameModes/GameplayGameMode.h"
#include "GameObjects/CardsHand.h"

#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

using namespace Core;

void AIPlayer::BeginPlay()
{
	Super::BeginPlay();
	// TODO: Add AI COntroller which will make all choices

	m_WinSound = AssetManager::Get().Load<SoundAsset>("S_Tada")->SoundP;
}

void AIPlayer::Tick(float deltaTime)
{

}

void AIPlayer::AllowToPlay()
{
	Super::AllowToPlay();
	// TODO: Add callbacks
}

void AIPlayer::AllowTurn()
{
	Super::AllowTurn();
	if (m_State->AllowedToBet)
		TimerManager::Get().StartTimer(1000, [this]() { PlaceBet(); });

	if (m_State->FinishedGame)
	{
		return;
	}

	if (m_State->AllowedToTurn)
		TimerManager::Get().StartTimer(3000, [this]() { MakeTurn(); });
}

void AIPlayer::GameResult(EPlayerResult result)
{
	Super::GameResult(result);

	switch (result)
	{
	case EPlayerResult::Lose:
		AudioSystem::PlaySound(m_LoseSound);
		break;
	case EPlayerResult::BlackjackWin:
	case EPlayerResult::DefaultWin:
		AudioSystem::PlaySound(m_WinSound);
		break;
	case EPlayerResult::Push:
		AudioSystem::PlaySound(m_ErrorSound);
		break;
	}
}

void AIPlayer::PlaceBet()
{
	int32 minBet = GameState->MinBet;
	int32 maxBet = glm::min(GameState->MaxBet, m_Balance);
	std::uniform_int_distribution<> distrBet(minBet, maxBet);
	int32 bet = distrBet(gen);
	m_SelectedChips = m_Bet.lock()->SelectChips(bet);
	BJ_LOG_INFO("%s: Generated bet: %d", GetTag().c_str(), bet);

	PlaceChipFromSelected();
}

void AIPlayer::MakeTurn()
{
	BJ_LOG_INFO("Make turn %s", GetTag().c_str());
	EAIDecision decision = MakeDecision();
	switch (decision)
	{
	case EAIDecision::Hit:
		Hit();
		break;
	case EAIDecision::Stand:
		Stand();
		break;
	case EAIDecision::DoubleDown:
	{
		if (CanDoubleDown())
			DoubleDown();
		else
			Hit();
		break;
	}
	}
}

AIPlayer::EAIDecision AIPlayer::MakeDecision()
{
	EAIDecision decision = EAIDecision::Hit;
	if (const auto& hand = m_Cards.lock())
	{
		int32 handValue = hand->CalculateHandValue();
		int32 dealerHandValue = GameState->CurrentDealerHandValue;
		int32 dealerUpCard = GameState->CurrentDealerHandValue;
		bool hasAce = hand->HasAce();
		std::uniform_int_distribution<> randomRisk(1, 100);

		// 1. If the bot has a hand value of 17 or more, always stand
		if (handValue >= 17)
		{
			decision = EAIDecision::Stand;
			return decision;
		}

		// 2. Double Down decisions (usually for hands 9, 10, or 11)
		if (handValue >= 9 && handValue <= 11)
		{
			// If the dealer has a weak card (2-6), consider doubling down
			if (dealerUpCard >= 2 && dealerUpCard <= 6)
			{
				// Introduce a random chance to double down (let's say 70% for strong hands)
				if (randomRisk(gen) <= 70)
				{
					decision = EAIDecision::DoubleDown;
					return decision;
				}
			}
			// If dealer has a strong card (7+), still consider doubling but with less chance
			else if (dealerUpCard >= 7)
			{
				if (randomRisk(gen) <= 40) // 40% chance to double down
				{
					decision = EAIDecision::DoubleDown;
					return decision;
				}
			}
		}
		// 3. If the bot has a hand value between 12-16, decide based on the dealer's up card
		if (handValue >= 12 && handValue <= 16)
		{
			// If the dealer's up card is between 2 and 6, the dealer is likely to bust, so stand
			if (dealerUpCard >= 2 && dealerUpCard <= 6)
			{
				// Random chance to still take a risk and hit
				if (randomRisk(gen) <= 20) // 20% chance to hit
				{
					decision = EAIDecision::Hit;;
					return decision;
				}
				decision = EAIDecision::Stand;
				return decision;
			}
			// Otherwise, hit with a small chance of standing if hand is decent
			if (randomRisk(gen) <= 30) // 30% chance to stand
			{
				decision = EAIDecision::Stand;
				return decision;
			}
			decision = EAIDecision::Hit;
			return decision;
		}

		// 4. If the bot has a hand value less than 12, always hit
		if (handValue < 12)
		{
			decision = EAIDecision::Hit;
			return decision;
		}

		// 5. Soft hands (Ace included, e.g., Ace+2 to Ace+10)
		if (hasAce && handValue <= 17)
		{
			// A soft 17 or less is risky, so we may take a chance to hit
			if (randomRisk(gen) <= 40) // 40% chance to hit on soft hand
			{
				decision = EAIDecision::Hit;
				return decision;
			}

			// If dealer has a weak card (2-6), the bot may stand
			if (dealerUpCard >= 2 && dealerUpCard <= 6)
			{
				decision = EAIDecision::Stand;
				return decision;
			}

			// Otherwise, hit by default
			decision = EAIDecision::Hit;
			return decision;
		}

		// 6. Optional: Consider a very risky move with very weak cards
		// If bot is really feeling lucky or has a very low hand, introduce more randomness
		if (handValue < 8)
		{
			if (randomRisk(gen) <= 50) // 50% chance to take a risky hit
			{
				decision = EAIDecision::Hit;
				return decision;
			}
		}
	}
	return decision;
}


void AIPlayer::PlaceChipFromSelected()
{
	EChipType chip = m_SelectedChips.front();
	m_SelectedChips.pop_front();

	PlaceChip(chip);

	if (m_SelectedChips.empty())
	{
		ConfirmBet();
	}
	else
	{
		std::uniform_int_distribution<>	distrTime(400, 1000);
		m_TimerHandle_PlaceBet = TimerManager::Get().StartTimer(distrTime(gen), [this]() { PlaceChipFromSelected(); });
	}
}


