#include "GameObjects/Player.h"

#include "GameObjects/ChipStack.h"
#include "GameObjects/CardsHand.h"
#include "GameModes/GameplayGameMode.h"


#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>

using namespace Core;

Player::Player()
{
	m_ConfirmSound = AssetManager::Get().Load<SoundAsset>("S_Confirm")->SoundP;
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


}

void Player::PlaceChip(EChipType chip)
{
	if (auto bet = m_Bet.lock())
	{
		bet->CorrectRotation();
		bet->AddChip(chip);
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
	SharedPtr<GameplayGameMode> GM = static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode());
	GM->BetPlacedEvent();
	AudioSystem::PlaySound(m_ConfirmSound);
}

void Player::SetState(SharedPtr<PlayerState> state)
{
	m_State = state;
}

bool Player::HasBalance()
{
	// TODO: Change to check balance
	return true;
}

void Player::AllowToPlay()
{
	RoundStateMachine& gameState = static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode())->GetGameState();
	gameState.OnBettingStageStarted.Add([=]() { m_State->AllowedToBet = true; });

	BJ_LOG_INFO("%s allowed to play", GetTag().c_str());
}

void Player::AllowTurn()
{
	m_State->ActiveTurn = true;
}

void Player::ForbidTurn()
{
	m_State->ActiveTurn = false;
}
bool Player::IsMyTurn()
{
	return m_State->ActiveTurn;
}
