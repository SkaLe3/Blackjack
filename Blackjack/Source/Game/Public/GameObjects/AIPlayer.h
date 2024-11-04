#pragma once
#include "GameObjects/Player.h"


class AIPlayer : public Player
{
	DECLARE_SUPER(Player)
public:				
	//~ Begin Object Interface
	virtual void Tick(float deltaTime) override;
	//~ End Object Interface

	void PlaceBet();

};