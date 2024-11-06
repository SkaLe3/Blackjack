#include "GameObjects/Player.h"

#include "GameObjects/ChipStack.h"
#include "GameObjects/CardsHand.h"
#include "GameModes/GameplayGameMode.h"	// TODO: remove if possible


#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>
#include <Core/TimerManager.h>

using namespace Core;

Player::Player()
{
	m_ConfirmSound = AssetManager::Get().Load<SoundAsset>("S_Confirm")->SoundP;
	m_ErrorSound = AssetManager::Get().Load<SoundAsset>("S_Error")->SoundP;
	m_LoseSound = AssetManager::Get().Load<SoundAsset>("S_Fail")->SoundP;

	m_State = MakeShared<PlayerState>();
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	auto bet = GetWorld()->SpawnGameObject<ChipStack>();
	bet->AttachToObject(GetSelf());
	bet->GetTransform().Translation.y = 3;
	bet->GetTransform().Translation.z = 10;
	m_Bet = bet;

	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 1, 0, 1, 1 }));  // Magenta
	GetBoxComponent()->SetHalfSize({ 2, 2 });

	OnChipAction.Add([](int32 value) { BJ_LOG_INFO("BetValue: %d", value); }); // TODO : Replace with UI function
}

void Player::SetBalance(int32 balace)
{
	m_Balance = balace;
}

void Player::AddBalance(int32 amount)
{
	m_Balance += amount;
}

void Player::PlaceChip(EChipType chip)
{
	if (auto bet = m_Bet.lock())
	{
		if ((byte)chip + bet->GetBetValue() > m_Balance)
		{
			BJ_LOG_INFO("Chip not placed! Not enought balance to add $%d", (int32)(byte)chip);
			AudioSystem::PlaySound(m_ErrorSound);
			return;
		}
		bet->CorrectRotation();	// For corner players
		bool placed = bet->AddChip(chip);
		if (!placed)
		{
			AudioSystem::PlaySound(m_ErrorSound);
			return;
		}
		OnChipAction.Broadcast(bet->GetBetValue()); // TODO: Bind UI function to update text label
	}
}

void Player::TakeLastChip()
{
	if (auto bet = m_Bet.lock())
	{
		bet->RemoveChip();
	}
}

void Player::ConfirmBet()
{
	if (auto bet = m_Bet.lock())
	{
		int32 value = bet->GetBetValue();
		if (value < GameState->MinBet || value > GameState->MaxBet)
		{
			// To avoid redutant branching in Release build
#ifdef BJ_DEBUG
			if (value < GameState->MinBet)
			{
				BJ_LOG_INFO("Cannot confirm bet! Bet is below the minimum. Bet: $%d | MinBet: $%d", value, GameState->MinBet);
			}
			else
			{
				BJ_LOG_INFO("Cannot confirm bet! Bet is above the maximum. Bet: $%d | MinBet: $%d", value, GameState->MaxBet);
			}
#endif 
			AudioSystem::PlaySound(m_ErrorSound);
			return;
		}
		GameState->OnBetPlaced.Broadcast();
		AudioSystem::PlaySound(m_ConfirmSound);
		BJ_LOG_INFO("Bet placed! Player: %s", GetTag().c_str());

	}

}

int32 Player::GetBetValue()
{
	if (const auto& bet = m_Bet.lock())
	{
		return bet->GetBetValue();
	}
	return 0;
}

void Player::ClearBet()
{
	if (const auto& bet = m_Bet.lock())
	{
		bet->Clear();
	}
}

void Player::ResetBetPosition()
{
	m_Bet.lock()->GetTransform().Translation.y = 3;
	m_Bet.lock()->GetTransform().Translation.z = 10;
}

SharedPtr<ChipStack> Player::GiveBetToDealer()
{
	 return m_Bet.lock();
}

void Player::CallBlackjack()
{
	GameState->OnPlayerCallBlackjack.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::Hit()
{
	Super::Hit();
	GameState->OnPlayerHit.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
}

void Player::Stand()
{
	Super::Stand();
	GameState->OnPlayerStand.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::Bust()
{
	Super::Bust();
	GameState->OnPlayerBust.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
}

bool Player::TryDoubleDown()
{
	bool canDD = CanDoubleDown();
	if (canDD)
	{
		DoubleDown();
		return true;
	}
	AudioSystem::PlaySound(m_ErrorSound);
	return false;
}

bool Player::CanDoubleDown()
{
	if (auto bet = m_Bet.lock())
	{
		if (bet->GetBetValue() * 2 > GameState->MaxBet)
		{
			BJ_LOG_INFO("DoubleDown refused! Doubled bet is over max bet limit");
			return false;
		}
		if (bet->GetBetValue() * 2 > m_Balance)
		{
			BJ_LOG_INFO("DoubleDown refused! Not enough balance");
			return false;
		}
		bool doubled = bet->Double();
		if (!doubled)
		{
			BJ_LOG_INFO("DoubleDown refused! exceed maximum chip count in bet");
			return false;
		}
	}
	return true;
}

void Player::DoubleDown()
{
	GameState->OnPlayerDoubleDown.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::DealerBust()
{
	GameState->OnPlayerResultWin.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
}

void Player::OverDealer()
{
	GameState->OnPlayerResultWin.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
}

void Player::UnderDealer()
{
	GameState->OnPlayerResultLose.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
}

void Player::Push()
{
	GameState->OnPlayerResultPush.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
}

void Player::Split()
{
   // Will be in the future
}

void Player::ResetState()
{
	m_State = MakeShared<PlayerState>();
}

int32 Player::GetBalance()
{
	return m_Balance;
}

void Player::AllowToPlay()
{
	m_State = MakeShared<PlayerState>(); // Reset
	// Consider moving this to GameMode
	GameState->OnBettingStageStarted.Add([this]() { m_State->AllowedToBet = true; });
	GameState->OnDealingcardsStageStarted.Add([this]() { m_State->AllowedToBet = false; });
	GameState->OnPlayerTurnStageStarted.Add([this]() { m_State->AllowedToTurn = true; });
	GameState->OnDealerRevealStageStarted.Add([this]() { m_State->AllowedToTurn = false; });
	GameState->OnRoundResultStageStarted.Add([this]() { m_State->AllowedToCheckResult = true; });

	BJ_LOG_INFO("%s allowed to play", GetTag().c_str());
}

void Player::AllowTurn()
{
	m_State->ActiveTurn = true;
	BJ_LOG_INFO("%s Turn:", GetTag().c_str());

	if (m_State->AllowedToTurn) { TurnInitialCheck(); }
	if (m_State->AllowedToCheckResult) { CheckResult(); }
}


void Player::TurnInitialCheck()
{
	if (auto hand = m_Cards.lock())
	{
		int32 handValue = hand->CalculateHandValue();
		if (handValue == 21 && hand->GetCardCount() == 2)
		{
			ForbidTurn();
			TimerManager::Get().StartTimer(2000.f, [this]() { CallBlackjack(); }); // Wait a bit before ending turn
			m_State->FinishedGame = true;
		}
		else if (handValue > 21)
		{
			ForbidTurn();
			TimerManager::Get().StartTimer(2000.f, [this]() { Bust(); });
			m_State->FinishedGame = true;
		}
	}
}

void Player::CheckResult()
{
	ForbidTurn();
	m_State->FinishedGame = true;
	if (auto hand = m_Cards.lock())
	{
		int32 handValue = hand->CalculateHandValue();
		if (GameState->CurrentDealerHandValue > 21)
		{
			TimerManager::Get().StartTimer(2000.f, [this]() { DealerBust(); });
		}
		else if (GameState->CurrentDealerHandValue > handValue)
		{
			TimerManager::Get().StartTimer(2000.f, [this]() { UnderDealer(); });
		}
		else if (GameState->CurrentDealerHandValue < handValue)
		{
			TimerManager::Get().StartTimer(2000.f, [this]() { OverDealer(); });
		}
		else
		{
			TimerManager::Get().StartTimer(2000.f, [this]() { Push(); });
		}

	}
}

void Player::ForbidTurn()
{
	m_State->ActiveTurn = false;
}
bool Player::IsMyTurn()
{
	return m_State->ActiveTurn;
}

bool Player::HasFinishedGame()
{
	return m_State->FinishedGame;
}

void Player::AskForNextRound()
{
	m_State->AskForNextRound = true;
}
