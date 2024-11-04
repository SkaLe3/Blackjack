#pragma once
#include <World/Entities/GameMode.h>
#include <Core/Event.h>

class ChipStack;
class Player;
class Deck;

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
	SharedPtr<Deck> m_Deck;
	SharedPtr<Player> m_Player;
	SharedPtr<Player> m_Bot1;
	SharedPtr<Player> m_Bot2;
};