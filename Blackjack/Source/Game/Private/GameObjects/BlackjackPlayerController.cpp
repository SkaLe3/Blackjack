#include "GameObjects/BlackjackPlayerController.h"

#include "Widgets/HUDWidgetLayout.h"
#include "GameModes/GameplayGameMode.h"
#include "GameObjects/UserPlayer.h"

using namespace  Core;

void BlackjackPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CreateHUD();
	auto player = std::static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode())->GetUserPlayer();
	Posses(player);
	m_UserPlayer = player;

}

void BlackjackPlayerController::CreateHUD()
{
	if (SharedPtr<HUDWidgetLayout> myWidget = CreateWidgetLayout<HUDWidgetLayout>("HUD"))
	{
		myWidget->SetOwner(GetSelf().lock());
		myWidget->Init();
		myWidget->AddToViewport(2);
	}
}

void BlackjackPlayerController::TakeLastChip()
{
	if (m_UserPlayer->CanBet())
	{
		m_UserPlayer->TakeLastChip();
	}
}


void BlackjackPlayerController::PlaceSelectedChip(EChipType chip)
{
	if (m_UserPlayer->CanBet())
	{
		m_UserPlayer->PlaceChip(chip);
	}
}

void BlackjackPlayerController::ConfirmSelectedBet()
{
	if (m_UserPlayer->CanBet())
	{
		m_UserPlayer->ConfirmBet();
	}
}
