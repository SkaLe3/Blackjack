#pragma once
#include "GameObjects/Player.h"

#include <Core/Event.h> 

class UserPlayer : public Player
{
	DECLARE_SUPER(Player)
public:

	void OnEvent(Core::Event& event);
};