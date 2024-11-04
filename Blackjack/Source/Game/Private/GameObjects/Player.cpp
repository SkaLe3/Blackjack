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
	SET_BOX_DEBUG_COLOR((glm::vec4{1, 0, 1, 1}));  // Magenta
	GetBoxComponent()->SetHalfSize({2, 2});
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

