#pragma once
#include "GameObjects/Player.h"

#include <Core/Event.h> 

class UserPlayer : public Player
{
	DECLARE_SUPER(Player)
public:
	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ End Object Interface

	void OnEvent(Core::Event& event);
};