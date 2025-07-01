#include "Widgets/ChipStackValueWidgetLayout.h"
#include <UISystem/PanelWidget.h>
#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>
#include <UISystem/ViewportSystem.h>

#include "GameObjects/ChipStack.h"

using namespace Core;

void ChipStackValueWidgetLayout::Init()
{
	SharedPtr<PanelWidget> panel = MakeShared<PanelWidget>("ChipPanel");
	SetRootWidget(panel);

	auto betBg = MakeShared<ImageWidget>("BetBackground");
	Background = betBg;
	panel->AddChild(betBg);
	betBg->Slot->SetPosition({ 0, 0 });
	betBg->Slot->SetSize({ 44, 44 });
	betBg->Slot->SetAlignment({ 0.5f, 0.5f });
	betBg->Slot->SetZOrder(10);
	betBg->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_BetBg")->TextureP));



	auto betText = MakeShared<TextWidget>("bot1bet");
	Value = betText;
	panel->AddChild(betText);
	betText->Slot->SetPosition({ 0, 1 });
	betText->Slot->SetSize({ 50, 50 });
	betText->Slot->SetAlignment({ 0.5f, 0.5f });
	betText->Slot->SetZOrder(11);
	betText->SetText("0");
	betText->SetFont("BebasNeue-Regular-28");
	betText->SetColor({ 0.9f, 0.9f, 0.9f, 1.0f });

	WidgetLayout::Init();
}

void ChipStackValueWidgetLayout::Tick(float deltaTime)
{
	WidgetLayout::Tick(deltaTime);

	SharedPtr<ChipStack> bet = PlayerStack.lock();
	Enable(false);
	if (bet != nullptr)
	{
		int32 betAmount = bet->GetBetValue();
		if (betAmount > 0)
		{
			Enable(true);
		}
		SetValue(betAmount);
	}

	Transform betTransform = bet->GetWorldTransform();
	glm::vec2 betScreenCoords = betTransform.Translation;
	betScreenCoords = ViewportSystem::Get().WorldToScreen(betScreenCoords);
	betScreenCoords.x += 80;
	betScreenCoords.y += 20;
	SetPosition(betScreenCoords);
}

void ChipStackValueWidgetLayout::SetPosition(const glm::vec2& newPos)
{
	Slot->SetPosition(newPos);
}

void ChipStackValueWidgetLayout::SetValue(int32 value)
{
	SharedPtr<TextWidget> textValue = Value.lock();
	if (textValue)
	{
		textValue->SetText(std::to_string(value));
	}
}

void ChipStackValueWidgetLayout::Enable(bool bEnable)
{
	SetVisibility(bEnable);
}

void ChipStackValueWidgetLayout::ProvideStacks(SharedPtr<ChipStack> chipStack)
{
	PlayerStack = chipStack;
}
