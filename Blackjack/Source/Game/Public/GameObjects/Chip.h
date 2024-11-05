#pragma once
#include <World/Entities/SpriteObject.h>

#include <unordered_map>
#include <vector>

enum class EChipType : byte
{
	White = 1,
	Red = 5,
	Blue = 10,
	Gray = 20,
	Green = 25,
	Orange = 50
};

class Chip : public Core::SpriteObject
{
	DECLARE_SUPER(Core::SpriteObject)
public:
	Chip();

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	float GetHeight();
	void SetHeight(float height);

	EChipType GetType();
	void SetType(EChipType chip);
	float GetValue();

public:

	static std::unordered_map<EChipType, String> ChipsMap;
	static const std::vector<std::pair<EChipType, const int>> ChipsValues;

private:
	float m_Height = 1.11;

	EChipType m_ChipType;


};