#include "GameObjects/BlackjackPlayerController.h"

#include "Widgets/HUDWidgetLayout.h"
#include "GameModes/GameplayGameMode.h"
#include "GameObjects/UserPlayer.h"

#include "Widgets/ChipStackValueWidgetLayout.h"
#include "Widgets/CardsScoreWidgetLayout.h"
#include "GameObjects/CardsHand.h"
#include "GameObjects/Dealer.h"

using namespace  Core;

void BlackjackPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto player = std::static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode())->GetUserPlayer();
	Posses(player);
	m_UserPlayer = player;
	CreateHUD();
}

void BlackjackPlayerController::PostBeginPlay()
{
	PlayerController::PostBeginPlay();

	std::vector<SharedPtr<Player>> players = static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode())->GetPlayers();
	std::vector<SharedPtr<ChipStack>> stacks;
	std::vector<SharedPtr<CardsHand>> hands;
	for (auto player : players)
	{
		stacks.push_back(player->GetBetObject());
		hands.push_back(player->GetCardsHand());
	}
	ProcessBetStacks(stacks);

	hands.push_back(static_pointer_cast<GameplayGameMode>(GetWorld()->GetGameMode())->GetDealer()->GetCardsHand());
	ProcessCardsHands(hands);
}

void BlackjackPlayerController::CreateHUD()
{
	if (SharedPtr<HUDWidgetLayout> myWidget = CreateWidgetLayout<HUDWidgetLayout>("HUD"))
	{
		m_HUD = myWidget;
		myWidget->SetOwner(GetSelf().lock());
		myWidget->AddToViewport(2);
		m_UserPlayer->OnPlayerBalanceChanged.Add([=](int32 newBalance)
			{
				SharedPtr<TextWidget> balanceWidget = myWidget->Balance.lock();
				if (balanceWidget) balanceWidget->SetText(std::to_string(newBalance));
			});
		SharedPtr<TextWidget> balanceWidget = myWidget->Balance.lock();
		if (balanceWidget) balanceWidget->SetText(std::to_string(m_UserPlayer->GetBalance()));

		
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

void BlackjackPlayerController::CallStand()
{
	if (m_UserPlayer->CanMakeTurn())
	{
		m_UserPlayer->Stand();
	}
}

void BlackjackPlayerController::CallHit()
{
	if (m_UserPlayer->CanMakeTurn())
	{
		m_UserPlayer->Hit();
	}
}

void BlackjackPlayerController::ProcessBetStacks(std::vector<SharedPtr<ChipStack>> stacks)
{
	SharedPtr<HUDWidgetLayout> hud = m_HUD.lock();
	if (hud != nullptr)
	{
		for (size_t i = 0; i < stacks.size(); i++)
		{
			if (SharedPtr<ChipStackValueWidgetLayout> playerBetWidget = dynamic_pointer_cast<ChipStackValueWidgetLayout>(hud->PlayerBets[i].lock()))
			{
				playerBetWidget->ProvideStacks(stacks[i]);
			}
		}
	}
}

void BlackjackPlayerController::ProcessCardsHands(std::vector<SharedPtr<CardsHand>> hands)
{
	SharedPtr<HUDWidgetLayout> hud = m_HUD.lock();
	if (hud != nullptr)
	{
		for (size_t i = 0; i < hands.size(); i++)
		{
			if (SharedPtr<CardsScoreWigetLayout> scoreWidget = dynamic_pointer_cast<CardsScoreWigetLayout>(hud->CardsHands[i].lock()))
			{
				scoreWidget->ProvideHand(hands[i]);
				if (i == 0) scoreWidget->SetOffset({ 60, -160 });
				if (i == 1) scoreWidget->SetOffset({ 0, -170 });
				if (i == 2) scoreWidget->SetOffset({ -60, -160 });
				if (i == 3) scoreWidget->SetOffset({ 0, -170 });
			}
		}
	}
}


void BlackjackPlayerController::OnAskForNextRound(int32 resultType)
{
	SharedPtr<HUDWidgetLayout> hud = m_HUD.lock();
	if (hud != nullptr)
	{
		hud->RoundOverScreen(true,resultType, 0.8f);
	}
}

void BlackjackPlayerController::OnContinueToNextRound()
{
	SharedPtr<HUDWidgetLayout> hud = m_HUD.lock();
	if (hud != nullptr)
	{
		hud->RoundOverScreen(false,0, 0.8f);
	}
}

void BlackjackPlayerController::OnTurnChanged(const String& playerName)
{
	SharedPtr<HUDWidgetLayout> hud = m_HUD.lock();
	if (hud != nullptr)
	{
		hud->SetTurnText(playerName);
	}
}
