#pragma once
#include <World/Entities/PlayerController.h>

#include "GameObjects/Chip.h"


class UserPlayer;
class HUDWidgetLayout;
class ChipStack;
class CardsHand;

class BlackjackPlayerController : public Core::PlayerController
{
	DECLARE_SUPER(Core::PlayerController)
public:
	virtual void BeginPlay() override;
	virtual void PostBeginPlay() override;
	void CreateHUD();

	void TakeLastChip();
	void PlaceSelectedChip(EChipType chip);
	void ConfirmSelectedBet();
	void CallStand();
	void CallHit();

	void ProcessBetStacks(std::vector<SharedPtr<ChipStack>> stacks);
	void ProcessCardsHands(std::vector<SharedPtr<CardsHand>> hands);
	void OnAskForNextRound(int32 resultType);
	void OnContinueToNextRound();

	SharedPtr<UserPlayer> m_UserPlayer;
	WeakPtr<HUDWidgetLayout> m_HUD;

};