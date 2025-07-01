#pragma once
#include <UISystem/WidgetLayout.h>

#include <UISystem/Widgets/ImageWidget.h>
#include <UISystem/Widgets/TextWidget.h>

class CardsHand;

class CardsScoreWigetLayout : public Core::WidgetLayout
{
public:
	CardsScoreWigetLayout(const String& inName) : Core::WidgetLayout(inName) {}
	virtual void Init() override;
	virtual void Tick(float deltaTime) override;

	void SetPosition(const glm::vec2& newPos);
	void SetValue(int32 value);
	void Enable(bool bEnable);
	void SetOffset(const glm::vec2& offset);

	void ProvideHand(SharedPtr<CardsHand> cardsHand);
public:
	WeakPtr<Core::ImageWidget> Background;
	WeakPtr<Core::TextWidget> Value;
	WeakPtr<CardsHand> Hand;
	glm::vec2 Offset;
};