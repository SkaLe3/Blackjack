#pragma once
#include <World/Entities/PlayerController.h>

#include "GameObjects/Chip.h"


class UserPlayer;

class BlackjackPlayerController : public Core::PlayerController
{
	DECLARE_SUPER(Core::PlayerController)
public:
	virtual void BeginPlay() override;
	void CreateHUD();

	void TakeLastChip();
	void PlaceSelectedChip(EChipType chip);
	void ConfirmSelectedBet();
	void CallStand();
	void CallHit();

	SharedPtr<UserPlayer> m_UserPlayer;

};