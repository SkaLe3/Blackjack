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

	//~ Begin Player Interface
	virtual void GameResult(EPlayerResult result) override;
	virtual void AllowTurn() override;
	//~ End Player Interface

	void OnEvent(Core::Event& event);


private:
	SharedPtr<Core::SoundBase> m_WinSound;
	SharedPtr<Core::SoundBase> m_YipeeSound;
	SharedPtr<Core::SoundBase> m_FailJingle;


};