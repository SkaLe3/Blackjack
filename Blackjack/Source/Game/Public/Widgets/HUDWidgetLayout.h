#pragma once
#include <UISystem/WidgetLayout.h>

#include <UISystem/Widgets/ImageWidget.h>
#include <UISystem/Widgets/ButtonWidget.h>

#include <World/Entities/GameObject.h>

class BlackjackPlayerController;

class HUDWidgetLayout : public Core::WidgetLayout
{
public:
	HUDWidgetLayout(const String& inName) : Core::WidgetLayout(inName) {}

	virtual void Init() override;

	void SetOwner(SharedPtr<Core::GameObject> pc);

public:
	WeakPtr<Core::ImageWidget> UIBar;
	WeakPtr<Core::ImageWidget> Dollar;
	WeakPtr<Core::ImageWidget> MinMaxBet;
	WeakPtr<Core::ImageWidget> BetAmount;
	WeakPtr<Core::ImageWidget> WinAmount;
	WeakPtr<Core::ButtonWidget> ChangeSkinButton;
	WeakPtr<Core::ButtonWidget> MinusButton;
	WeakPtr<Core::ButtonWidget> ConfirmButton;
	WeakPtr<Core::ButtonWidget> WhiteChipButton;
	WeakPtr<Core::ButtonWidget> RedChipButton;
	WeakPtr<Core::ButtonWidget> BlueChipButton;
	WeakPtr<Core::ButtonWidget> GrayChipButton;
	WeakPtr<Core::ButtonWidget> GreenChipButton;
	WeakPtr<Core::ButtonWidget> OrangeChipButton;


private:
	SharedPtr<BlackjackPlayerController> m_PlayerController;

};
