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

	void AddChip(EChipType chip);
	void RemoveChip();
	uint32 GetChipsCount();
	

private:
   	std::stack<SharedPtr<Chip>> m_Chips;
	SharedPtr<Core::TextureAtlas> m_ChipsTexture;

	SharedPtr<Core::SoundBase> m_ChipSetSound;
	SharedPtr<Core::SoundBase> m_ChipRemoveSound;
};