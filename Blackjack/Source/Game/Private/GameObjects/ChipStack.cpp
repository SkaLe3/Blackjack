#include "GameObjects/ChipStack.h"

#include "GameObjects/Chip.h"
#include "Assets/ChipTextureAtlas.h"
#include "Components/ChipStackMovementComponent.h"

#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>


using namespace Core;

ChipStack::ChipStack() : GameObject()
{
	m_ChipsTexture = MakeShared<ChipTextureAtlas>();
	m_ChipSetSound = AssetManager::Get().Load<SoundAsset>("S_PokerChip")->SoundP;
	m_ChipRemoveSound = AssetManager::Get().Load<SoundAsset>("S_PokerChips")->SoundP;
	m_ErrorSound = AssetManager::Get().Load<SoundAsset>("S_Error")->SoundP;
	m_MovementComp = CreateComponent<ChipStackMovementComponent>();
}

void ChipStack::BeginPlay()
{
	Super::BeginPlay();
	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 1, 0, 0, 1 })); // Red
	GetBoxComponent()->SetHalfSize({ 2, 2 });

	GetMovementComponent()->SetOwner(GetSelf());
}

void ChipStack::Destroy()
{
   Super::Destroy();
   GetMovementComponent()->Destroy();
}

bool ChipStack::AddChip(EChipType chip)
{
	if (m_MaxChipsInBet <= m_Chips.size())
	{
		BJ_LOG_INFO("Chip not placed! Max bet amount reached");
		return false;
	}
	SharedPtr<Chip> topChip = GetWorld()->SpawnGameObject<Chip>();
	topChip->AttachToObject(GetSelf());
	topChip->GetTransform().Translation.y = GetChipsCount() * topChip->GetHeight();
	topChip->GetTransform().Translation.z = GetChipsCount() * topChip->GetHeight();
	auto spriteComp = topChip->GetSpriteComponent();
	spriteComp->SetAtlas(m_ChipsTexture);
	topChip->SetType(chip);
	m_Chips.push_back(topChip);
	AudioSystem::PlaySound(m_ChipSetSound);
	return true;
}

void ChipStack::RemoveChip()
{
	if (!m_Chips.empty())
	{
		m_Chips.back()->Destroy();
		m_Chips.pop_back();

		AudioSystem::PlaySound(m_ChipRemoveSound);
	}


}

bool ChipStack::Double()
{
	if (m_MaxChipsInBet < m_Chips.size() * 2)
	{
		return false;
	}
	std::vector<SharedPtr<Chip>> chips = m_Chips;
	for (auto& chip : chips)
	{
		AddChip(chip->GetType());
	}
	AudioSystem::PlaySound(m_ChipRemoveSound); // Combine Add and Remove sounds
	return true;
}

uint32 ChipStack::GetChipsCount()
{
	return m_Chips.size();
}

int32 ChipStack::GetBetValue()
{
	int32 sum = 0;
	for (auto& chip : m_Chips)
	{
		byte chipValue = (byte)(chip->GetType());
		sum += chipValue;
	}
	return sum;
}

std::list<EChipType> ChipStack::SelectChips(int32 value)
{
	std::list<EChipType> selectedChips;

	std::uniform_int_distribution<> distr(0, 1); // Decide to skip or not

	for (const auto& [chipType, chipValue] : Chip::ChipsValues)
	{
		while (value >= chipValue)
		{
			if (distr(gen) == 0 || chipValue == 1)
			{
				selectedChips.push_back(chipType);
				value -= chipValue;
			}
		}
		if (value == 0) break;
	}
	if (value != 0)
	{
		// This should never happen
		selectedChips.pop_back();
	}
	return selectedChips;
}

void ChipStack::Move(float duration, const glm::vec2& start, const glm::vec2& target)
{
   GetMovementComponent()->StartMovement(duration, start, target);
}

void ChipStack::CorrectRotation()
{
	SharedPtr<GameObject> parent = GetOwner();
	if (parent)
	{
		float parentRotation = parent->GetWorldTransform().Rotation.z;
		GetTransform().Rotation.z = -parentRotation;

	}
}

void ChipStack::Clear()
{
	for (auto& chip : m_Chips)
	{
		chip->Destroy();
	}
	m_Chips.clear();
}

SharedPtr<ChipStackMovementComponent> ChipStack::GetMovementComponent()
{
	return m_MovementComp.lock();
}
