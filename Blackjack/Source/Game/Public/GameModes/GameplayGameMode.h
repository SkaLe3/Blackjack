#pragma once
#include <World/Entities/GameMode.h>
#include <Core/Event.h>

class ChipStack;

class GameplayGameMode : public Core::GameMode
{
	DECLARE_SUPER(Core::GameMode)
public:
	GameplayGameMode() = default;
	~GameplayGameMode() = default;

	void OnEvent(Core::Event& event);

	//~ Begin Object Interface
	virtual void BeginPlay() override;
	//~ Eng Object Interface

	void RestartGame();
	void LeaveGame();

private:
	// TESTING
	SharedPtr<ChipStack> m_ChipStack;
};