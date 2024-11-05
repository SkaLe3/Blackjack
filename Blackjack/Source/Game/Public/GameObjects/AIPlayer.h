#pragma once
#include "GameObjects/Player.h"


class AIPlayer : public Player
{
	DECLARE_SUPER(Player)
public:				
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	//~ Begin Player Interface
	virtual void AllowToPlay() override;
	virtual void AllowTurn() override;
	//~ End Player Interface

	void PlaceBet();



};