#include "GameObjects/Player.h"

#include "GameObjects/ChipStack.h"
#include "GameObjects/CardsHand.h"
#include "GameModes/GameplayGameMode.h"


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

	OnChipAction.Add([](uint32 value) { BJ_LOG_INFO("BetValue: %d", value); }); // TODO : Replace with UI function
}

void Player::SetBalance(uint32 balace)
{
	m_Balance = balace;
}

void Player::AddBalance(uint32 amount)
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
		uint32 value = bet->GetBetValue();
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

void Player::CallBlackjack()
{
	GameState->OnPlayerCallBlackjack.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::Hit()
{
	GameState->OnPlayerHit.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::Stand()
{
	GameState->OnPlayerStand.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::DoubleDown()
{
	if (auto bet = m_Bet.lock())
	{
		if (bet->GetBetValue() * 2 > GameState->MaxBet)
		{
			BJ_LOG_INFO("DoubleDown refused! Doubled bet is over max bet limit");
			AudioSystem::PlaySound(m_ErrorSound);
			return;
		}
		if (bet->GetBetValue() * 2 > m_Balance)
		{
			BJ_LOG_INFO("DoubleDown refused! Not enough balance");
			AudioSystem::PlaySound(m_ErrorSound);
			return;
		}
		bool doubled = bet->Double();
		if (!doubled)
		{
			BJ_LOG_INFO("DoubleDown refused! exceed maximum chip count in bet");
			AudioSystem::PlaySound(m_ErrorSound);
			return;
		}
		GameState->OnPlayerDoubleDown.Broadcast(std::static_pointer_cast<Player>(GetSelf().lock()));
		AudioSystem::PlaySound(m_ConfirmSound);
	}
}

void Player::Split()
{

}

void Player::SetState(SharedPtr<PlayerState> state)
{
	m_State = state;
}

uint32 Player::GetBalance()
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


	BJ_LOG_INFO("%s allowed to play", GetTag().c_str());
}

void Player::AllowTurn()
{
	m_State->ActiveTurn = true;
	BJ_LOG_INFO("%s Turn:", GetTag().c_str());

	if (m_State->AllowedToTurn)
	{
		if (auto hand = m_Cards.lock())
		{
			if (hand->CalculateHandValue() >15)
			{	
				ForbidTurn();
				TimerManager::Get().StartTimer(2000.f, [this](){ CallBlackjack();}); // Wait a bit before ending turn
				m_State->FinishedGame = true;
			}
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
