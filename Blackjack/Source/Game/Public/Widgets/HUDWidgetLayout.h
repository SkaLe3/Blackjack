#pragma once
#include <UISystem/WidgetLayout.h>

#include <UISystem/Widgets/ImageWidget.h>
#include <UISystem/Widgets/ButtonWidget.h>
#include <UISystem/Widgets/ToggleButtonWidget.h>
#include <UISystem/Widgets/TextWidget.h>

#include <World/Entities/GameObject.h>

class BlackjackPlayerController;

class HUDWidgetLayout : public Core::WidgetLayout
{
public:
	HUDWidgetLayout(const String& inName);

	virtual void Init() override;
	virtual void Tick(float deltaTime) override;

	void SetOwner(SharedPtr<Core::GameObject> pc);
	void RoundOverScreen(bool bStatus,int32 resultType, float fadeTime = 1.f);
	void RoundOverScreenTick(float deltaTime);
	void FpsCounterTick(float deltaTime);

	void SetResultWin();
	void SetResultBlackjack();
	void SetResultLose();
	void SetResultPush();
	void HideResult();
	void ResultTick(float deltaTime);

	void SetTurnText(const String& inPlayerName);
public:
	WeakPtr<Core::ImageWidget> UIBar;
	WeakPtr<Core::ImageWidget> TurnPlate;
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
	WeakPtr<Core::ButtonWidget> StandButton;
	WeakPtr<Core::ButtonWidget> HitButton;

	WeakPtr<Core::TextWidget> Balance;

	std::vector< WeakPtr<Core::WidgetLayout>> PlayerBets;
	std::vector<WeakPtr<Core::WidgetLayout>> CardsHands;

	WeakPtr<Core::ButtonWidget> ContinueButton;
	WeakPtr<Core::ButtonWidget> QuitButton;
	WeakPtr<Core::ToggleButtonWidget> MuteMusicButton;
	WeakPtr<Core::ToggleButtonWidget> MuteAmbientButton;
	WeakPtr<Core::ToggleButtonWidget> MuteSoundButton;

	WeakPtr<Core::ImageWidget> AfterRound;
	WeakPtr<Core::TextWidget> ResultText;
	WeakPtr<Core::TextWidget> TurnText;

	WeakPtr<Core::ImageWidget> Vingete; // TODO: Make separate

	WeakPtr<Core::TextWidget> FpsCounter;

private:
	SharedPtr<BlackjackPlayerController> m_PlayerController;
	float m_RoundOverScreenAlpha = 0.0f;
	float m_RoundOverFadeTime = 1.0f;
	bool m_bFadeIn = true;
	bool m_bRoundOverScreenFading = false;

	float m_ResultAlpha = 0.0f;
	float m_ResultFadeTime = 1.0f;
	bool m_bResultFadeIn = true;
	bool m_bResultFading = false;

};
