#include "Widgets/HUDWidgetLayout.h"

#include <UISystem/PanelWidget.h>

#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>
#include "Assets/ChipTextureAtlas.h"

#include "GameObjects/BlackjackPlayerController.h"
#include "GameObjects/Chip.h"

using namespace Core;

void HUDWidgetLayout::Init()
{
	SharedPtr<PanelWidget> panel = MakeShared<PanelWidget>("panel");

	auto uibar = MakeShared<ImageWidget>("UIBar");
	UIBar = uibar;
	panel->AddChild(uibar);
	uibar->Slot->SetPosition({ 0, 1080 });
	uibar->Slot->SetSize({ 1920, 147 });
	uibar->Slot->SetAlignment({ 0.f, 1.f });
	uibar->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_UIBar")->TextureP));

	auto dollar = MakeShared<ImageWidget>("Dollar");
	Dollar = dollar;
	panel->AddChild(dollar);
	dollar->Slot->SetPosition({ 131, 952 });
	dollar->Slot->SetSize({ 75, 110 });
	dollar->Slot->SetAlignment({ 0.f, 0.f });
	dollar->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_Dollar")->TextureP));

	auto minmaxBet = MakeShared<ImageWidget>("MinMaxBet");
	MinMaxBet = minmaxBet;
	panel->AddChild(minmaxBet);
	minmaxBet->Slot->SetPosition({ 1460, 70 });
	minmaxBet->Slot->SetSize({ 360, 200 });
	minmaxBet->Slot->SetAlignment({ 0.f, 0.f });
	minmaxBet->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_MinMaxBet")->TextureP));

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


	SharedPtr<Texture> changeSkinTex = AssetManager::Get().Load<TextureAsset>("T_ChangeSkin")->TextureP;
	auto changeSkingButton = MakeShared<ButtonWidget>("ChangeSkin");
	ChangeSkinButton = changeSkingButton;
	panel->AddChild(changeSkingButton);
	changeSkingButton->Slot->SetPosition({ 20, 960.f });
	changeSkingButton->Slot->SetSize({ 100.f, 102.f });
	changeSkingButton->Slot->SetAlignment({ 0.f, 0.0f });
	changeSkingButton->SetImage(Sprite::Create(changeSkinTex));

	SharedPtr<Texture> minusTex = AssetManager::Get().Load<TextureAsset>("T_Minus")->TextureP;
	auto minusButton = MakeShared<ButtonWidget>("Minus");
	MinusButton = minusButton;
	panel->AddChild(minusButton);
	minusButton->Slot->SetPosition({ 1230, 1006.f });
	minusButton->Slot->SetSize({ 80, 15 });
	minusButton->Slot->SetAlignment({ 0.f, 0.0f });
	minusButton->SetImage(Sprite::Create(minusTex));
	minusButton->OnButtonClick.Add([=](int32 button)
								   {
									   if (button == 1)	m_PlayerController->TakeLastChip();
								   }) ;

	SharedPtr<Texture> confirm = AssetManager::Get().Load<TextureAsset>("T_ConfirmBet")->TextureP;
	auto confirmButton = MakeShared<ButtonWidget>("Minus");
	ConfirmButton = confirmButton;
	panel->AddChild(confirmButton);
	confirmButton->Slot->SetPosition({ 1230, 1006.f });
	confirmButton->Slot->SetSize({ 80, 15 });
	confirmButton->Slot->SetAlignment({ 0.f, 0.0f });
	confirmButton->SetImage(Sprite::Create(minusTex));
	confirmButton->OnButtonClick.Add([=](int32 button)
								   {
									   if (button == 1)	m_PlayerController->ConfirmSelectedBet();
								   });


	SharedPtr<Texture> chipsTex = AssetManager::Get().Load<TextureAsset>("T_ChipUIAtlas")->TextureP;
	SharedPtr<ChipTextureAtlas> chipsAtlas = MakeShared<ChipTextureAtlas>(chipsTex);
	auto whiteChipButton = MakeShared<ButtonWidget>("WhiteChip");
	WhiteChipButton = whiteChipButton;
	panel->AddChild(whiteChipButton);
	whiteChipButton->Slot->SetPosition({ 1315, 1010 });
	whiteChipButton->Slot->SetSize({ 100, 100 });
	whiteChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	whiteChipButton->SetAtlas(chipsAtlas);
	whiteChipButton->SetRegion("white");
	whiteChipButton->OnButtonClick.Add([=](int32 button)
								   {
									   if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::White);
								   }) ;


	auto redChipButton = MakeShared<ButtonWidget>("RedChip");
	RedChipButton = redChipButton;
	panel->AddChild(redChipButton);
	redChipButton->Slot->SetPosition({ 1415, 1010 });
	redChipButton->Slot->SetSize({ 100, 100 });
	redChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	redChipButton->SetAtlas(chipsAtlas);
	redChipButton->SetRegion("red");
	redChipButton->OnButtonClick.Add([=](int32 button)
								   {
									   if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Red);
								   }) ;

	auto blueChipButton = MakeShared<ButtonWidget>("BlueChip");
	BlueChipButton = blueChipButton;
	panel->AddChild(blueChipButton);
	blueChipButton->Slot->SetPosition({ 1515, 1010 });
	blueChipButton->Slot->SetSize({ 100, 100 });
	blueChipButton->Slot->SetAlignment({ 0.f, 0.5f });
	blueChipButton->SetAtlas(chipsAtlas);
	blueChipButton->SetRegion("blue");
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
	orangeChipButton->OnButtonClick.Add([=](int32 button)
									   {
										   if (button == 1)	m_PlayerController->PlaceSelectedChip(EChipType::Orange);
									   });

	SetRootWidget(panel);
}


void HUDWidgetLayout::SetOwner(SharedPtr<GameObject> pc)
{
	
	m_PlayerController = std::static_pointer_cast<BlackjackPlayerController>(pc);
}