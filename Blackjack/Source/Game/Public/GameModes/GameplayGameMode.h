#pragma once
#include <World/Entities/GameMode.h>

class GameplayGameMode : public Core::GameMode
{
	DECLARE_SUPER(Core::GameMode)
public:
	GameplayGameMode() = default;
	~GameplayGameMode() = default;

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ Eng Object Interface

	void RestartGame();
	void LeaveGame();
};