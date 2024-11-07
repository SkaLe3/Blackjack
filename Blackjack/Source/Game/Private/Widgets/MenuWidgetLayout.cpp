#include "Widgets/MenuWidgetLayout.h"

#include <UISystem/PanelWidget.h>

#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>

#include "Assets/MenuButtonTextureAtlas.h"


using namespace Core;

void MenuWidgetLayout::Init()
{
	SharedPtr<PanelWidget> panel = MakeShared<PanelWidget>("panel");

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
	startButton->SetRegion("play");

	auto leaveButton = MakeShared<ButtonWidget>("Leave");
	LeaveButton	= leaveButton;
	panel->AddChild(leaveButton);
	leaveButton->Slot->SetPosition({ 40, 620.f });
	leaveButton->Slot->SetSize({ 400.f, 80.f });
	leaveButton->Slot->SetAlignment({ 0.f, 0.5f });
	leaveButton->SetAtlas(buttonsTexture);
	leaveButton->SetRegion("leave");

	



	SetRootWidget(panel);
}
