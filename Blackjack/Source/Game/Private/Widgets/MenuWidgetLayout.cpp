#include "Widgets/MenuWidgetLayout.h"

#include <UISystem/PanelWidget.h>

#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>

#include "Assets/MenuButtonTextureAtlas.h"



using namespace Core;

void MenuWidgetLayout::Init()
{
	SharedPtr<PanelWidget> panel = MakeShared<PanelWidget>("panel");
	SetRootWidget(panel);
	auto clickSound = AssetManager::Get().Load<SoundAsset>("S_BtnLightClick")->SoundP;
	auto hoverSound = AssetManager::Get().Load<SoundAsset>("S_BtnHover")->SoundP;
	hoverSound->SetVolumeMultiplier(0.15f);

	// Background
	auto background = MakeShared<ImageWidget>("Background");
	Background = background;
	panel->AddChild(background);
	background->Slot->SetPosition({ 0, 0 });
	background->Slot->SetSize({ 1920, 1080 });
	background->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_MenuBackgroundFiltered")->TextureP));




	// Start Button
	SharedPtr<MenuButtonTextureAtlas> buttonsTexture = MakeShared<MenuButtonTextureAtlas>();
	auto startButton = MakeShared<ButtonWidget>("Start");
	StartButton = startButton;
	panel->AddChild(startButton);
	startButton->Slot->SetPosition({40, 500.f});
	startButton->Slot->SetSize({400.f, 80.f });
	startButton->Slot->SetAlignment({0.f, 0.5f});
	startButton->SetAtlas(buttonsTexture);
	startButton->SetRegion("play_default");
	startButton->SetClickSound(clickSound);
	startButton->SetHoverSound(hoverSound);
	startButton->SetHoverImage(buttonsTexture, "play_hover");
	startButton->SetPressImage(buttonsTexture, "play_press");

	auto leaveButton = MakeShared<ButtonWidget>("Leave");
	LeaveButton	= leaveButton;
	panel->AddChild(leaveButton);
	leaveButton->Slot->SetPosition({ 40, 740.f });
	leaveButton->Slot->SetSize({ 400.f, 80.f });
	leaveButton->Slot->SetAlignment({ 0.f, 0.5f });
	leaveButton->SetAtlas(buttonsTexture);
	leaveButton->SetRegion("leave_default");
	leaveButton->SetClickSound(clickSound);
	leaveButton->SetHoverSound(hoverSound);
	leaveButton->SetHoverImage(buttonsTexture, "leave_hover");
	leaveButton->SetPressImage(buttonsTexture, "leave_press");

	auto addSkinButton = MakeShared<ButtonWidget>("AddSkin");
	AddSkinButton = addSkinButton;
	panel->AddChild(addSkinButton);
	addSkinButton->Slot->SetPosition({ 40, 620.f });
	addSkinButton->Slot->SetSize({ 400.f, 80.f });
	addSkinButton->Slot->SetAlignment({ 0.f, 0.5f });
	addSkinButton->SetAtlas(buttonsTexture);
	addSkinButton->SetRegion("addSkin_default");
	addSkinButton->SetClickSound(clickSound);
	addSkinButton->SetHoverSound(hoverSound);
	addSkinButton->SetHoverImage(buttonsTexture, "addSkin_hover");
	addSkinButton->SetPressImage(buttonsTexture, "addSkin_press");

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
	muteMusicButton->SetColor({ 10.f, 10.0f, 10.0f });

	auto muteSoundButton = MakeShared<MuteButtonWidget>("MuteAmbient", "T_MuteFX");
	MuteSoundButton = muteSoundButton;
	panel->AddChild(muteSoundButton);
	muteSoundButton->Slot->SetPosition({ 10, 100 });
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


}


