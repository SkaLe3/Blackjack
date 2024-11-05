#pragma once
#include <World/Entities/GameObject.h> 
#include "GameObjects/Chip.h"

#include <Sound/Sound.h>

#include <stack>


class ChipStack : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	ChipStack();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	bool AddChip(EChipType chip);
	bool Double();
	void RemoveChip();
	uint32 GetChipsCount();
	uint32 GetBetValue();

	void CorrectRotation();


private:
	// Used vector instead of stack to be able to iterate through it
   	std::vector<SharedPtr<Chip>> m_Chips;
	SharedPtr<Core::TextureAtlas> m_ChipsTexture;

	SharedPtr<Core::SoundBase> m_ChipSetSound;
	SharedPtr<Core::SoundBase> m_ChipRemoveSound;
	SharedPtr<Core::SoundBase> m_ErrorSound;

	const int32 m_MaxChipsInBet = 20;
};