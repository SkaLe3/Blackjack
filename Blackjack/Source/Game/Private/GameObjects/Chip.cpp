#include "GameObjects/Chip.h"

#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>

using namespace Core;

std::unordered_map<EChipType, String> Chip::ChipsMap = {
	{EChipType::White, "white"},
	{EChipType::Red, "red"},
	{EChipType::Blue, "blue"},
	{EChipType::Gray, "gray"},
	{EChipType::Green, "green"},
	{EChipType::Orange, "orange"},
};

Chip::Chip()
{
	auto sprite = GetSpriteComponent();
	sprite->GetTransform().Scale = { 10, 10, 1 };
}

void Chip::BeginPlay()
{
	Super::BeginPlay();
}

float Chip::GetHeight()
{
	return m_Height;
}

void Chip::SetHeight(float height)
{
	m_Height = height;
}

EChipType Chip::GetType()
{
	return m_ChipType;
}

void Chip::SetType(EChipType chip)
{
	m_ChipType = chip;
	GetSpriteComponent()->SetRegion(ChipsMap[chip]);
}

float Chip::GetValue()
{
	return static_cast<float>(static_cast<byte>(m_ChipType));
}
