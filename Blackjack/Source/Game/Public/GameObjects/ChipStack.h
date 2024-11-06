#pragma once
#include <World/Entities/GameObject.h> 
#include "GameObjects/Chip.h"

#include <Sound/Sound.h>

#include <random>
#include <list>

class ChipStackMovementComponent;

class ChipStack : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	ChipStack();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Destroy() override;
	//~ End Object Interface

	bool AddChip(EChipType chip);
	bool Double();
	void RemoveChip();
	uint32 GetChipsCount();
	int32 GetBetValue();
	std::list<EChipType> SelectChips(int32 value);

	void Move(float duration, const glm::vec2& start, const glm::vec2& target);
	void CorrectRotation();
	void Clear();

	SharedPtr<ChipStackMovementComponent> GetMovementComponent();
private:
	WeakPtr<ChipStackMovementComponent> m_MovementComp;
   	std::vector<SharedPtr<Chip>> m_Chips;
	SharedPtr<Core::TextureAtlas> m_ChipsTexture;

	SharedPtr<Core::SoundBase> m_ChipSetSound;
	SharedPtr<Core::SoundBase> m_ChipRemoveSound;
	SharedPtr<Core::SoundBase> m_ErrorSound;

	const int32 m_MaxChipsInBet = 20;

	std::random_device rd;
	std::mt19937 gen{ rd() };
};