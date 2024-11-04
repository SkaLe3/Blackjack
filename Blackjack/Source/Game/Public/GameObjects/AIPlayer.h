#pragma once
#include "GameObjects/Player.h"


class AIPlayer : public Player
{
	DECLARE_SUPER(Player)
public:				
	void PlaceBet();

};