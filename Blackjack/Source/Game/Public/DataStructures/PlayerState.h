#pragma once


enum class EPlayerResult
{
	None = 0,
	BlackjackWin,
	DefaultWin,
	Push,
	Lose
};

struct PlayerState
{
	bool ActiveTurn = false;
	bool AllowedToBet = false;
	bool AllowedToTurn = false;
	bool FinishedGame = false;
	EPlayerResult RoundResult = EPlayerResult::None;
};