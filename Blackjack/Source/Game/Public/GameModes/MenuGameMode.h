#pragma once
#include "World/Entities/GameMode.h"

#include <Core/Event.h>

class MenuGameMode : public Core::GameMode
{
	DECLARE_SUPER(Core::GameMode)
public:
	MenuGameMode() = default;
	~MenuGameMode() = default;

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ Eng Object Interface

	void OnEvent(Core::Event& event);

	void RestartMenu();
	void StartGame();
	void AddSkin();	// Add Skin to game

	void CreateMenuWidget();
};