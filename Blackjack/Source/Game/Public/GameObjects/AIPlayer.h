#pragma once
#include "GameObjects/Player.h"
#include "Core/TimerManager.h"

#include <random>
#include <list>

class AIPlayer : public Player
{
	DECLARE_SUPER(Player)
public:		
	enum class EAIDecision
	{
		Hit,
		Stand,
		DoubleDown
	};

public:
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	//~ Begin Player Interface
	virtual void AllowToPlay() override;
	virtual void AllowTurn() override;

	virtual void GameResult(EPlayerResult result) override;
	//~ End Player Interface

	void PlaceBet();
	void MakeTurn();
	EAIDecision MakeDecision();

private:
	std::list<EChipType> SelectChips(int32 value);	
	void PlaceChipFromSelected();

private:
	Core::TimerHandle m_TimerHandle_PlaceBet = 0;

	std::random_device rd;
	std::mt19937 gen{rd()};
	std::list<EChipType> m_SelectedChips;

	SharedPtr<Core::SoundBase> m_WinSound;

};