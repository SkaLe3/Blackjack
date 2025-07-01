#include "Widgets/CardsScoreWidgetLayout.h"
#include <UISystem/PanelWidget.h>
#include <Core/AssetManager.h>
#include <Renderer/Sprite.h>
#include <UISystem/ViewportSystem.h>

#include "GameObjects/CardsHand.h"


using namespace Core;

void CardsScoreWigetLayout::Init()
{
	SharedPtr<PanelWidget> panel = MakeShared<PanelWidget>("CardsPanel");
	SetRootWidget(panel);

	auto scoreBg = MakeShared<ImageWidget>("CardsScoreBackground");
	Background = scoreBg;
	panel->AddChild(scoreBg);
	scoreBg->Slot->SetPosition({ 0, 0 });
	scoreBg->Slot->SetSize({ 60, 60 });
	scoreBg->Slot->SetAlignment({ 0.5f, 0.5f });
	scoreBg->Slot->SetZOrder(11);
	scoreBg->SetImage(Sprite::Create(AssetManager::Get().Load<TextureAsset>("T_ScoreBg")->TextureP));



	auto scoreText = MakeShared<TextWidget>("ScoreText");
	Value = scoreText;
	panel->AddChild(scoreText);
	scoreText->Slot->SetPosition({ 0, 1 });
	scoreText->Slot->SetSize({ 50, 50 });
	scoreText->Slot->SetAlignment({ 0.5f, 0.5f });
	scoreText->Slot->SetZOrder(12);
	scoreText->SetText("0");
	scoreText->SetFont("BebasNeue-Regular-32");
	scoreText->SetColor({ 1.0f, 210.f * 1.f/255.f, 0.0f, 1.0f });

	Offset = { 0, -200 };

	WidgetLayout::Init();
}

void CardsScoreWigetLayout::Tick(float deltaTime)
{
	WidgetLayout::Tick(deltaTime);

	SharedPtr<CardsHand> hand = Hand.lock();
	Enable(false);
	if (hand != nullptr)
	{
		int32 score = hand->CalculateHandValue();
		if (score > 0)
		{
			Enable(true);
		}
		SetValue(score);
	}

	Transform scoreTransform = hand->GetWorldTransform();
	glm::vec2 scoreScreenCoords = scoreTransform.Translation;
	scoreScreenCoords = ViewportSystem::Get().WorldToScreen(scoreScreenCoords);
	scoreScreenCoords.x += Offset.x;
	scoreScreenCoords.y += Offset.y;
	SetPosition(scoreScreenCoords);
}

void CardsScoreWigetLayout::SetPosition(const glm::vec2& newPos)
{
	Slot->SetPosition(newPos);
}

void CardsScoreWigetLayout::SetValue(int32 value)
{
	SharedPtr<TextWidget> textValue = Value.lock();
	if (textValue)
	{
		textValue->SetText(std::to_string(value));
	}
}

void CardsScoreWigetLayout::Enable(bool bEnable)
{
	SetVisibility(bEnable);
}

void CardsScoreWigetLayout::SetOffset(const glm::vec2& offset)
{
	Offset = offset;
}

void CardsScoreWigetLayout::ProvideHand(SharedPtr<CardsHand> cardsHand)
{
	Hand = cardsHand;
}
