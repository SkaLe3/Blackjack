#include "GameObjects/ChipStack.h"

#include "GameObjects/Chip.h"


void ChipStack::AddChip()
{
   m_Chips.push(GetWorld()->SpawnGameObject<Chip>());
}

void ChipStack::RemoveChip()
{
   m_Chips.pop();
}

uint32 ChipStack::GetChipsCount()
{
	return m_Chips.size();
}
