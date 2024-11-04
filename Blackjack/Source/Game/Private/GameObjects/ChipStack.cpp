#include "GameObjects/ChipStack.h"

#include "GameObjects/Chip.h"
#include "Assets/ChipTextureAtlas.h"

#include <Sound/AudioSystem.h>
#include <Core/AssetManager.h>


using namespace Core;

ChipStack::ChipStack() : GameObject()
{
	m_ChipsTexture = MakeShared<ChipTextureAtlas>();
	m_ChipSetSound = AssetManager::Get().Load<SoundAsset>("S_PokerChip")->SoundP;
	m_ChipRemoveSound = AssetManager::Get().Load<SoundAsset>("S_PokerChips")->SoundP;
}

void ChipStack::BeginPlay()
{
	Super::BeginPlay();
	SET_BOX_DEBUG_VISIBILITY(true);
	SET_BOX_DEBUG_COLOR((glm::vec4{ 1, 0, 0, 1 })); // Red
	GetBoxComponent()->SetHalfSize({ 2, 2 });
}

void ChipStack::AddChip(EChipType chip)
{
	SharedPtr<Chip> topChip = GetWorld()->SpawnGameObject<Chip>();
	topChip->AttachToObject(GetSelf());
	topChip->GetTransform().Translation.y = GetChipsCount() * topChip->GetHeight();
	topChip->GetTransform().Translation.z = GetChipsCount() * topChip->GetHeight();
	auto spriteComp = topChip->GetSpriteComponent();
	spriteComp->SetAtlas(m_ChipsTexture);
	topChip->SetType(chip);
	m_Chips.push(topChip);
	AudioSystem::PlaySound(m_ChipSetSound);
}

void ChipStack::RemoveChip()
{
	if (!m_Chips.empty())
	{
		m_Chips.top()->Destroy();
		m_Chips.pop();

		AudioSystem::PlaySound(m_ChipRemoveSound);
	}


}

uint32 ChipStack::GetChipsCount()
{
	return m_Chips.size();
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
