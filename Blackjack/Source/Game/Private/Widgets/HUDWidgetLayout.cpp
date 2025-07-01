#include "Widgets/HUDWidgetLayout.h"

#include <UISystem/PanelWidget.h>

#include <Core/AssetManager.h>
#include <Sound/AudioSystem.h>
#include <Renderer/Sprite.h>
#include "Assets/ChipTextureAtlas.h"

#include "GameObjects/BlackjackPlayerController.h"
#include "GameObjects/Chip.h"
#include "GameModes/GameplayGameMode.h"
#include "GameObjects/UserPlayer.h"

#include "Widgets/ChipStackValueWidgetLayout.h"
#include "Widgets/CardsScoreWidgetLayout.h"
#include "Widgets/MuteButtonWidget.h"
#include "DataStructures/GameSettings.h"

using namespace Core;

HUDWidgetLayout::HUDWidgetLayout(const String& inName) : Core::WidgetLayout(inName)
{
	SharedPtr<PanelWidget> panel = MakeShared<PanelWidget>("panel");
	SetRootWidget(panel);

	auto bot1BetValue = MakeShared<ChipStackValueWidgetLayout>("Bot1Bet");
	auto playerBetValue = MakeShared<ChipStackValueWidgetLayout>("PlayerBet");
	auto bot2BetValue = MakeShared<ChipStackValueWidgetLayout>("Bot2Bet");
	PlayerBets.push_back(bot1BetValue);
	PlayerBets.push_back(playerBetValue);
	PlayerBets.push_back(bot2BetValue);
	panel->AddChild(bot1BetValue);
	panel->AddChild(playerBetValue);
	panel->AddChild(bot2BetValue);

	for (size_t i = 0; i < 4; i++)
	{
		auto scoreValue = MakeShared<CardsScoreWigetLayout>(String("Score") + std::to_string(i));
		CardsHands.push_back(scoreValue);
		panel->AddChild(scoreValue);
	}
}

void HUDWidgetLayout::Init()
{
	SharedPtr<PanelWidget> panel = RootWidget;

	for (size_t i = 0; i < PlayerBets.size(); i++)
	{
		SharedPtr<WidgetLayout> betValue = PlayerBets[i].lock();
		betValue->Slot->SetPosition({ 280, 840 });
		betValue->Slot->SetSize({ 100, 100 });
		betValue->Slot->SetAlignment({ 0.5f, 0.5f });
		betValue->Slot->SetZOrder(5);
	}

	for (size_t i = 0; i < CardsHands.size(); i++)
	{
		SharedPtr<WidgetLayout> scoreValue = CardsHands[i].lock();
		scoreValue->Slot->SetPosition({ 280, 840 });
		scoreValue->Slot->SetSize({ 100, 100 });
		scoreValue->Slot->SetAlignment({ 0.5f, 0.5f });
		scoreValue->Slot->SetZOrder(6);
	}

	auto clickSound = AssetManager::Get().Load<SoundAsset>("S_BtnLightClick")->SoundP;
	auto hoverSound = AssetManager::Get().Load<SoundAsset>("S_BtnHover")->SoundP;
	hoverSound->SetVolumeMultiplier(0.15f);
	clickSound->SetVolumeMultiplier(1.2f);

	auto uibar = MakeShared<ImageWidget>("UIBar");
	UIBar = uibar;
	panel->AddChild(uibar);
	uibar->Slot->SetPosition({ 0, 1080 });
	uibar->Slot->SetSize({ 1920, 160 });
	uibar->Slot->SetAlignment({ 0.f, 1.f });
	uibar->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_UIBar")->TextureP));

	auto vingete = MakeShared<ImageWidget>("Vingete");
	Vingete = vingete;
	panel->AddChild(vingete);
	vingete->Slot->SetPosition({ 0, 0 });
	vingete->Slot->SetSize({ 1920, 1080 });
	vingete->Slot->SetAlignment({ 0.f, 0.f });
	vingete->Slot->SetZOrder(20);
	vingete->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Vingete")->TextureP));

	auto dollar = MakeShared<ImageWidget>("Dollar");
	Dollar = dollar;
	panel->AddChild(dollar);
	dollar->Slot->SetPosition({ 131, 952 });
	dollar->Slot->SetSize({ 110, 110 });
	dollar->Slot->SetAlignment({ 0.f, 0.f });
	dollar->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Dollar")->TextureP));

	auto minmaxBet = MakeShared<ImageWidget>("MinMaxBet");
	MinMaxBet = minmaxBet;
	panel->AddChild(minmaxBet);
	minmaxBet->Slot->SetPosition({ 1880, 40 });
	minmaxBet->Slot->SetSize({ 360, 200 });
	minmaxBet->Slot->SetAlignment({ 1.f, 0.f });
	minmaxBet->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_MinMaxBet")->TextureP));

#if 0
	auto betAmount = MakeShared<ImageWidget>("BetAmount");
	BetAmount = betAmount;
	panel->AddChild(betAmount);
	betAmount->Slot->SetPosition({ 600, 1005 });
	betAmount->Slot->SetSize({ 297, 60 });
	betAmount->Slot->SetAlignment({ 0.f, 0.f });
	betAmount->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_BetUI")->TextureP));

	auto winAmount = MakeShared<ImageWidget>("WinAmount");
	WinAmount = winAmount;
	panel->AddChild(winAmount);
	winAmount->Slot->SetPosition({ 920, 1005 });
	winAmount->Slot->SetSize({ 297, 60 });
	winAmount->Slot->SetAlignment({ 0.f, 0.f });
	winAmount->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_WinUI")->TextureP));

#endif 


	auto muteMusicButton = MakeShared<MuteButtonWidget>("MuteMusic", "T_MuteMusic");
	MuteMusicButton = muteMusicButton;
	panel->AddChild(muteMusicButton);
	muteMusicButton->Slot->SetPosition({ 10, 10 });
	muteMusicButton->Slot->SetSize({ 80, 80 });
	muteMusicButton->Slot->SetAlignment({ 0.0f, 0.0f });
	muteMusicButton->SetClickSound(clickSound);
	muteMusicButton->SetHoverSound(hoverSound);
	muteMusicButton->OnToggleEnabled.Add([=](int32 button)
		{
			if (button == 1) AudioSystem::PauseMusic();
		});
	muteMusicButton->OnToggleDisabled.Add([=](int32 button)
		{
			if (button == 1) AudioSystem::ResumeMusic();
		});
	muteMusicButton->SetVisibility(true);
	muteMusicButton->Slot->SetZOrder(20);
	muteMusicButton->SetActivityState(AudioSystem::IsMusicMuted());

	auto muteAmbientButton = MakeShared<MuteButtonWidget>("MuteAmbient", "T_MuteAmbient");
	MuteAmbientButton = muteAmbientButton;
	panel->AddChild(muteAmbientButton);
	muteAmbientButton->Slot->SetPosition({ 10, 100 });
	muteAmbientButton->Slot->SetSize({ 80, 80 });
	muteAmbientButton->Slot->SetAlignment({ 0.0f, 0.0f });
	muteAmbientButton->SetClickSound(clickSound);
	muteAmbientButton->SetHoverSound(hoverSound);
	muteAmbientButton->OnToggleEnabled.Add([=](int32 button)
		{
			if (button == 1) AudioSystem::StopSound(GameSettings::AmbientSoundActive);
		});
	muteAmbientButton->OnToggleDisabled.Add([=](int32 button)
		{
			if (button == 1) GameSettings::AmbientSoundActive = AudioSystem::PlaySound(GameSettings::AmbientSound);
		});
	muteAmbientButton->SetVisibility(true);
	muteAmbientButton->Slot->SetZOrder(20);
	muteAmbientButton->SetActivityState(GameSettings::bAmbientMuted);

	auto muteSoundButton = MakeShared<MuteButtonWidget>("MuteAmbient", "T_MuteFX");
	MuteSoundButton = muteSoundButton;
	panel->AddChild(muteSoundButton);
	muteSoundButton->Slot->SetPosition({ 10, 190 });
	muteSoundButton->Slot->SetSize({ 80, 80 });
	muteSoundButton->Slot->SetAlignment({ 0.0f, 0.0f });
	muteSoundButton->SetClickSound(clickSound);
	muteSoundButton->SetHoverSound(hoverSound);
	muteSoundButton->OnToggleEnabled.Add([=](int32 button)
		{
			if (button == 1) AudioSystem::MuteSound();
		});
	muteSoundButton->OnToggleDisabled.Add([=](int32 button)
		{
			if (button == 1)  AudioSystem::UnmuteSound();
		});
	muteSoundButton->SetVisibility(true);
	muteSoundButton->Slot->SetZOrder(20);
	muteSoundButton->SetActivityState(AudioSystem::IsSoundMuted());
	

	SharedPtr<Texture> changeSkinTex = AssetManager::Get().Load<TextureAsset>("T_ChangeSkin")->TextureP;
	SharedPtr<TextureAtlas> changeSkinAtlas = MakeShared<TextureAtlas>(changeSkinTex);
	changeSkinAtlas->AddRegion("skin_default", { 0, 0, 512, 512 });
	changeSkinAtlas->AddRegion("skin_hover", { 0, 512, 512, 512 });
	changeSkinAtlas->AddRegion("skin_press", { 512, 0, 512, 512 });

	auto changeSkingButton = MakeShared<ButtonWidget>("ChangeSkin");
	ChangeSkinButton = changeSkingButton;
	panel->AddChild(changeSkingButton);
	changeSkingButton->Slot->SetPosition({ 20, 952.f });
	changeSkingButton->Slot->SetSize({ 110, 110 });
	changeSkingButton->Slot->SetAlignment({ 0.f, 0.0f });
	changeSkingButton->SetAtlas(changeSkinAtlas);
	changeSkingButton->SetRegion("skin_default");
	changeSkingButton->SetClickSound(clickSound);
	changeSkingButton->SetHoverSound(hoverSound);
	changeSkingButton->SetHoverImage(changeSkinAtlas, "skin_hover");
	changeSkingButton->SetPressImage(changeSkinAtlas, "skin_press");
	changeSkingButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)
			{
				auto gameMode = std::static_pointer_cast<GameplayGameMode>(m_PlayerController->GetWorld()->GetGameMode());
				gameMode->CycleCardSkin();
			}
		});

	SharedPtr<Texture> minusTex = AssetManager::Get().Load<TextureAsset>("T_Minus")->TextureP;
	SharedPtr<TextureAtlas> minusAtlas = MakeShared<TextureAtlas>(minusTex);
	minusAtlas->AddRegion("default", { 0, 0, 90, 90 });
	minusAtlas->AddRegion("hover", { 1 * 90, 0, 90, 90 });
	minusAtlas->AddRegion("press", { 2 * 90, 0, 90, 90 });

	auto minusButton = MakeShared<ButtonWidget>("Minus");
	MinusButton = minusButton;
	panel->AddChild(minusButton);
	minusButton->Slot->SetPosition({ 1228, 970.f });
	minusButton->Slot->SetSize({ 90, 90 });
	minusButton->Slot->SetAlignment({ 0.f, 0.0f });
	minusButton->SetAtlas(minusAtlas);
	minusButton->SetRegion("default");
	minusButton->SetClickSound(clickSound);
	minusButton->SetHoverSound(hoverSound);
	minusButton->SetHoverImage(minusAtlas, "hover");
	minusButton->SetPressImage(minusAtlas, "press");
	minusButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->TakeLastChip();
		});

	SharedPtr<Texture> confirm = AssetManager::Get().Load<TextureAsset>("T_ConfirmBet")->TextureP;
	SharedPtr<TextureAtlas> confirmAtlas = MakeShared<TextureAtlas>(confirm);
	confirmAtlas->AddRegion("confirm_default", { 0, 0, 280, 280 });
	confirmAtlas->AddRegion("confirm_hover", { 0,		0 + 280, 280, 280 });
	confirmAtlas->AddRegion("confirm_press", { 0 + 280,	0,		 280, 280 });

	auto confirmButton = MakeShared<ButtonWidget>("ConfirmBet");
	ConfirmButton = confirmButton;
	panel->AddChild(confirmButton);
	confirmButton->Slot->SetPosition({ 580, 1010 });
	confirmButton->Slot->SetSize({ 110, 110 });
	confirmButton->Slot->SetAlignment({ 0.f, 0.5f });
	confirmButton->SetAtlas(confirmAtlas);
	confirmButton->SetRegion("confirm_default");
	confirmButton->SetClickSound(clickSound);
	confirmButton->SetHoverSound(hoverSound);
	confirmButton->SetHoverImage(confirmAtlas, "confirm_hover");
	confirmButton->SetPressImage(confirmAtlas, "confirm_press");
	confirmButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->ConfirmSelectedBet();
		});


	SharedPtr<Texture> chipsTex = AssetManager::Get().Load<TextureAsset>("T_ChipUIAtlas")->TextureP;
	SharedPtr<ChipTextureAtlas> chipsAtlas = MakeShared<ChipTextureAtlas>(chipsTex);
	SharedPtr<Texture> chipsHoverTex = AssetManager::Get().Load<TextureAsset>("T_ChipUIAtlasHover")->TextureP;
	SharedPtr<ChipTextureAtlas> chipsHoverAtlas = MakeShared<ChipTextureAtlas>(chipsHoverTex);
	SharedPtr<Texture> chipsPressTex = AssetManager::Get().Load<TextureAsset>("T_ChipUIAtlasPress")->TextureP;
	SharedPtr<ChipTextureAtlas> chipsPressAtlas = MakeShared<ChipTextureAtlas>(chipsPressTex);

	auto whiteChipButton = MakeShared<ButtonWidget>("WhiteChip");
	WhiteChipButton = whiteChipButton;
	panel->AddChild(whiteChipButton);
	whiteChipButton->Slot->SetPosition({ 1315, 1010 });
	whiteChipButton->Slot->SetSize({ 100, 100 });
	whiteChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	whiteChipButton->SetAtlas(chipsAtlas);
	whiteChipButton->SetRegion("white");
	whiteChipButton->SetClickSound(clickSound);
	whiteChipButton->SetHoverSound(hoverSound);
	whiteChipButton->SetHoverImage(chipsHoverAtlas, "white");
	whiteChipButton->SetPressImage(chipsPressAtlas, "white");
	whiteChipButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::White);
		});


	auto redChipButton = MakeShared<ButtonWidget>("RedChip");
	RedChipButton = redChipButton;
	panel->AddChild(redChipButton);
	redChipButton->Slot->SetPosition({ 1415, 1010 });
	redChipButton->Slot->SetSize({ 100, 100 });
	redChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	redChipButton->SetAtlas(chipsAtlas);
	redChipButton->SetRegion("red");
	redChipButton->SetClickSound(clickSound);
	redChipButton->SetHoverSound(hoverSound);
	redChipButton->SetHoverImage(chipsHoverAtlas, "red");
	redChipButton->SetPressImage(chipsPressAtlas, "red");
	redChipButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Red);
		});

	auto blueChipButton = MakeShared<ButtonWidget>("BlueChip");
	BlueChipButton = blueChipButton;
	panel->AddChild(blueChipButton);
	blueChipButton->Slot->SetPosition({ 1515, 1010 });
	blueChipButton->Slot->SetSize({ 100, 100 });
	blueChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	blueChipButton->SetAtlas(chipsAtlas);
	blueChipButton->SetRegion("blue");
	blueChipButton->SetClickSound(clickSound);
	blueChipButton->SetHoverSound(hoverSound);
	blueChipButton->SetHoverImage(chipsHoverAtlas, "blue");
	blueChipButton->SetPressImage(chipsPressAtlas, "blue");
	blueChipButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Blue);
		});

	auto grayChipButton = MakeShared<ButtonWidget>("GrayChip");
	GrayChipButton = grayChipButton;
	panel->AddChild(grayChipButton);
	grayChipButton->Slot->SetPosition({ 1615, 1010 });
	grayChipButton->Slot->SetSize({ 100, 100 });
	grayChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	grayChipButton->SetAtlas(chipsAtlas);
	grayChipButton->SetRegion("gray");
	grayChipButton->SetClickSound(clickSound);
	grayChipButton->SetHoverSound(hoverSound);
	grayChipButton->SetHoverImage(chipsHoverAtlas, "gray");
	grayChipButton->SetPressImage(chipsPressAtlas, "gray");
	grayChipButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Gray);
		});

	auto greenChipButton = MakeShared<ButtonWidget>("GreenChip");
	GreenChipButton = greenChipButton;
	panel->AddChild(greenChipButton);
	greenChipButton->Slot->SetPosition({ 1715, 1010 });
	greenChipButton->Slot->SetSize({ 100, 100 });
	greenChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	greenChipButton->SetAtlas(chipsAtlas);
	greenChipButton->SetRegion("green");
	greenChipButton->SetClickSound(clickSound);
	greenChipButton->SetHoverSound(hoverSound);
	greenChipButton->SetHoverImage(chipsHoverAtlas, "green");
	greenChipButton->SetPressImage(chipsPressAtlas, "green");
	greenChipButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Green);
		});

	auto orangeChipButton = MakeShared<ButtonWidget>("OrangeChip");
	OrangeChipButton = orangeChipButton;
	panel->AddChild(orangeChipButton);
	orangeChipButton->Slot->SetPosition({ 1815, 1010 });
	orangeChipButton->Slot->SetSize({ 100, 100 });
	orangeChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	orangeChipButton->SetAtlas(chipsAtlas);
	orangeChipButton->SetRegion("orange");
	orangeChipButton->SetClickSound(clickSound);
	orangeChipButton->SetHoverSound(hoverSound);
	orangeChipButton->SetHoverImage(chipsHoverAtlas, "orange");
	orangeChipButton->SetPressImage(chipsPressAtlas, "orange");
	orangeChipButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Orange);
		});
	SharedPtr<Texture> standTex = AssetManager::Get().Load<TextureAsset>("T_stand")->TextureP;
	SharedPtr<TextureAtlas> standAtlas = MakeShared<TextureAtlas>(standTex);
	standAtlas->AddRegion("stand_default", { 0, 0, 512, 340 });
	standAtlas->AddRegion("stand_hover", { 0, 340, 512, 340 });
	standAtlas->AddRegion("stand_press", { 512, 0, 512, 340 });

	auto standButton = MakeShared<ButtonWidget>("Stand");
	StandButton = standButton;
	panel->AddChild(standButton);
	standButton->Slot->SetPosition({ 520, 780 });
	standButton->Slot->SetSize({ 204.8, 136 });
	standButton->Slot->SetAlignment({ 0.f, 0.0f });
	standButton->SetAtlas(standAtlas);
	standButton->SetRegion("stand_default");
	standButton->SetClickSound(clickSound);
	standButton->SetHoverSound(hoverSound);
	standButton->SetHoverImage(standAtlas, "stand_hover");
	standButton->SetPressImage(standAtlas, "stand_press");
	standButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->CallStand();
		});

	SharedPtr<Texture> hitTex = AssetManager::Get().Load<TextureAsset>("T_hit")->TextureP;
	SharedPtr<TextureAtlas> hitAtlas = MakeShared<TextureAtlas>(hitTex);
	hitAtlas->AddRegion("hit_default", { 0, 0, 512, 340 });
	hitAtlas->AddRegion("hit_hover", { 0, 340, 512, 340 });
	hitAtlas->AddRegion("hit_press", { 512, 0, 512, 340 });

	auto hitButton = MakeShared<ButtonWidget>("hit");
	HitButton = hitButton;
	panel->AddChild(hitButton);
	hitButton->Slot->SetPosition({ 1195, 780 });
	hitButton->Slot->SetSize({ 204.8, 136 });
	hitButton->Slot->SetAlignment({ 0.f, 0.0f });
	hitButton->SetAtlas(hitAtlas);
	hitButton->SetRegion("hit_default");
	hitButton->SetClickSound(clickSound);
	hitButton->SetHoverSound(hoverSound);
	hitButton->SetHoverImage(hitAtlas, "hit_hover");
	hitButton->SetPressImage(hitAtlas, "hit_press");
	hitButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1)	m_PlayerController->CallHit();
		});

	SharedPtr<Texture>  quitTex = AssetManager::Get().Load<TextureAsset>("T_Quit")->TextureP;
	SharedPtr<TextureAtlas> quitAtlas = MakeShared<TextureAtlas>(quitTex);
	quitAtlas->AddRegion("quit_default", { 0, 0, 512, 256 });
	quitAtlas->AddRegion("quit_hover", { 512, 0, 512, 256 });
	quitAtlas->AddRegion("quit_press", { 0, 256, 512, 256 });

	auto quitButton = MakeShared<ButtonWidget>("quit");
	QuitButton = quitButton;
	panel->AddChild(quitButton);
	quitButton->Slot->SetPosition({ 960 + 10, 600 });
	quitButton->Slot->SetSize({ 256, 128 });
	quitButton->Slot->SetAlignment({ 0.0f, 0.5f });
	quitButton->SetAtlas(quitAtlas);
	quitButton->SetRegion("quit_default");
	quitButton->SetClickSound(clickSound);
	quitButton->SetHoverSound(hoverSound);
	quitButton->SetHoverImage(quitAtlas, "quit_hover");
	quitButton->SetPressImage(quitAtlas, "quit_press");
	quitButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1) m_PlayerController->m_UserPlayer->QuitGame();
		});
	quitButton->SetVisibility(false);
	quitButton->Slot->SetZOrder(9);

	SharedPtr<Texture>  continueTex = AssetManager::Get().Load<TextureAsset>("T_Continue")->TextureP;
	SharedPtr<TextureAtlas> continueAtlas = MakeShared<TextureAtlas>(continueTex);
	continueAtlas->AddRegion("continue_default", { 0, 0, 512, 256 });
	continueAtlas->AddRegion("continue_hover", { 512, 0, 512, 256 });
	continueAtlas->AddRegion("continue_press", { 0, 256, 512, 256 });

	auto continueButton = MakeShared<ButtonWidget>("quit");
	ContinueButton = continueButton;
	panel->AddChild(continueButton);
	continueButton->Slot->SetPosition({ 960 - 10, 600 });
	continueButton->Slot->SetSize({ 256, 128 });
	continueButton->Slot->SetAlignment({ 1.0f, 0.5f });
	continueButton->SetAtlas(continueAtlas);
	continueButton->SetRegion("continue_default");
	continueButton->SetClickSound(clickSound);
	continueButton->SetHoverSound(hoverSound);
	continueButton->SetHoverImage(continueAtlas, "continue_hover");
	continueButton->SetPressImage(continueAtlas, "continue_press");
	continueButton->OnButtonClick.Add([=](int32 button)
		{
			if (button == 1) m_PlayerController->m_UserPlayer->ContinueToNextRound();
		});
	continueButton->SetVisibility(false);
	continueButton->Slot->SetZOrder(9);

	auto afterRoundImage = MakeShared<ImageWidget>("afterRound");
	AfterRound = afterRoundImage;
	panel->AddChild(afterRoundImage);
	afterRoundImage->Slot->SetPosition({ 0, 0 });
	afterRoundImage->Slot->SetSize({ 1920, 1080 });
	afterRoundImage->Slot->SetAlignment({ 0.f, 0.f });
	afterRoundImage->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_AfterRoundWhite")->TextureP));
	afterRoundImage->Slot->SetZOrder(8);
	afterRoundImage->SetVisibility(false);

	auto balance = MakeShared<TextWidget>("balance");
	Balance = balance;
	panel->AddChild(balance);
	balance->Slot->SetPosition({ 231, 1008 });
	balance->Slot->SetSize({ 300, 100 }); // Text widget ignores size, used only for debug
	balance->Slot->SetAlignment({ 0.f, 0.5f });
	balance->SetText("1234567890");
	balance->SetFont("BebasNeue-Regular-88");
	balance->SetColor({ 0.447f, 0.741f, 0.224f, 1.0f });

	auto resultText = MakeShared<TextWidget>("Result");
	ResultText = resultText;
	panel->AddChild(resultText);
	resultText->Slot->SetPosition({ 960, 450 });
	resultText->Slot->SetSize({ 100, 100 });
	resultText->Slot->SetAlignment({ 0.5f, 0.5f });
	resultText->SetText("Result Placeholder");
	resultText->SetFont("BebasNeue-Regular-150");
	resultText->SetColor({ 1.f, 1.f, 1.f, 1.f });
	resultText->Slot->SetZOrder(20);
	resultText->SetVisibility(false);

	WidgetLayout::Init();
}


void HUDWidgetLayout::Tick(float deltaTime)
{
	WidgetLayout::Tick(deltaTime);

	RoundOverScreenTick(deltaTime);
	ResultTick(deltaTime);
}

void HUDWidgetLayout::SetOwner(SharedPtr<GameObject> pc)
{

	m_PlayerController = std::static_pointer_cast<BlackjackPlayerController>(pc);
}

void HUDWidgetLayout::RoundOverScreen(bool bStatus, int32 resultType, float fadeTime)
{
	m_bRoundOverScreenFading = true;
	m_RoundOverFadeTime = fadeTime;
	m_bFadeIn = bStatus;
	m_RoundOverScreenAlpha = (float)(int32)(!bStatus);

	if (SharedPtr<ImageWidget> whiteScreen = AfterRound.lock())
	{
		whiteScreen->SetVisibility(true);
	}
	if (SharedPtr<ButtonWidget> continueButton = ContinueButton.lock())
	{
		continueButton->SetVisibility(true);
	}
	if (SharedPtr<ImageWidget> quitButton = QuitButton.lock())
	{
		quitButton->SetVisibility(true);
	}
	if (!bStatus)
	{
		HideResult();
		return;
	}
	switch (resultType)
	{
	case 0:
		SetResultWin();
		break;
	case 1:
		SetResultBlackjack();
		break;
	case 2:
		SetResultLose();
		break;
	case 3:
		SetResultPush();
		break;
	}
}

void HUDWidgetLayout::RoundOverScreenTick(float deltaTime)
{
	if (m_bRoundOverScreenFading)
	{
		float delta = deltaTime / m_RoundOverFadeTime;
		if (!m_bFadeIn)
		{
			delta = -delta;
		}
		m_RoundOverScreenAlpha += delta;
		if (glm::abs(m_RoundOverScreenAlpha - 0.5f) >= glm::abs((float)(int32)(m_bFadeIn)-0.5f))
		{
			m_RoundOverScreenAlpha = (float)(int32)(m_bFadeIn);
			m_bRoundOverScreenFading = false;
			if (SharedPtr<ImageWidget> whiteScreen = AfterRound.lock())
			{
				whiteScreen->SetVisibility(m_bFadeIn);
			}
			if (SharedPtr<ButtonWidget> continueButton = ContinueButton.lock())
			{
				continueButton->SetVisibility(m_bFadeIn);
			}
			if (SharedPtr<ImageWidget> quitButton = QuitButton.lock())
			{
				quitButton->SetVisibility(m_bFadeIn);
			}
		}
		if (SharedPtr<ImageWidget> whiteScreen = AfterRound.lock())
		{
			whiteScreen->SetAlpha(m_RoundOverScreenAlpha);
		}
		if (SharedPtr<ButtonWidget> continueButton = ContinueButton.lock())
		{
			continueButton->SetAlpha(m_RoundOverScreenAlpha);
		}
		if (SharedPtr<ImageWidget> quitButton = QuitButton.lock())
		{
			quitButton->SetAlpha(m_RoundOverScreenAlpha);
		}
	}
}

void HUDWidgetLayout::SetResultWin()
{
	m_bResultFading = true;
	m_bResultFadeIn = true;
	m_ResultAlpha = 0.0f;
	SharedPtr<TextWidget> resultText = ResultText.lock();
	if (resultText)
	{
		resultText->SetText("You Win!");
		resultText->SetColor({ 0.392f, 0.906f, 0.f, 0.8f });
	}
}

void HUDWidgetLayout::SetResultBlackjack()
{
	m_bResultFading = true;
	m_bResultFadeIn = true;
	m_ResultAlpha = 0.0f;
	SharedPtr<TextWidget> resultText = ResultText.lock();
	if (resultText)
	{
		resultText->SetText("Blackjack!");
		resultText->SetColor({ 0.392f, 0.906f, 0.f, 0.8f });
		resultText->SetVisibility(true);
	}
}

void HUDWidgetLayout::SetResultLose()
{
	m_bResultFading = true;
	m_bResultFadeIn = true;
	m_ResultAlpha = 0.0f;
	SharedPtr<TextWidget> resultText = ResultText.lock();
	if (resultText)
	{
		resultText->SetText("You Lose");
		resultText->SetColor({ 0.827f, 0.f, 0.f, 0.8f });
		resultText->SetVisibility(true);
	}
}

void HUDWidgetLayout::SetResultPush()
{
	m_bResultFading = true;
	m_bResultFadeIn = true;
	m_ResultAlpha = 0.0f;
	SharedPtr<TextWidget> resultText = ResultText.lock();
	if (resultText)
	{
		resultText->SetText("Push - It's a Tie");
		resultText->SetColor({ 1.0f, 0.824f, 0.f, 0.8f });
		resultText->SetVisibility(true);
	}
}

void HUDWidgetLayout::HideResult()
{
	m_bResultFading = true;
	m_bResultFadeIn = false;
	m_ResultAlpha = 1.0f;

	SharedPtr<TextWidget> resultText = ResultText.lock();
	if (resultText)
	{
		resultText->SetVisibility(true);
	}
}

void HUDWidgetLayout::ResultTick(float deltaTime)
{
	if (m_bResultFading)
	{
		float delta = deltaTime / m_ResultFadeTime;
		if (!m_bResultFadeIn)
		{
			delta = -delta;
		}
		m_ResultAlpha += delta;
		if (SharedPtr<TextWidget> resultText = ResultText.lock())
		{
			resultText->SetScale(glm::sin(m_ResultAlpha * 3.f) + (m_ResultAlpha - 0.2f) * (m_ResultAlpha - 0.2f) - 0.14f);
		}
		if (glm::abs(m_ResultAlpha - 0.5f) >= glm::abs((float)(int32)(m_bResultFadeIn)-0.5f))
		{
			m_ResultAlpha = (float)(int32)(m_bResultFadeIn);
			m_bResultFading = false;
			if (SharedPtr<TextWidget> resultText = ResultText.lock())
			{
				resultText->SetVisibility(m_bResultFadeIn);
			}
		}
		if (SharedPtr<TextWidget> resultText = ResultText.lock())
		{
			resultText->SetAlpha(m_ResultAlpha);
		}

	}
}
