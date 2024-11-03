#pragma once
#include <World/Entities/GameObject.h> 

#include <stack>

class Chip;

class ChipStack : public Core::GameObject
{
	DECLARE_SUPER(Core::GameObject)
public:
	void AddChip();
	void RemoveChip();
	uint32 GetChipsCount();
	

private:
   	std::stack<SharedPtr<Chip>> m_Chips;
};