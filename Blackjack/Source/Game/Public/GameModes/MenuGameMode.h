#pragma once
#include "World/Entities/GameMode.h"

class MenuGameMode : public Core::GameMode
{
	DECLARE_SUPER(Core::GameMode)
public:
	MenuGameMode() = default;
	~MenuGameMode() = default;

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ Eng Object Interface

	void RestartMenu();
	void StartGame();
};