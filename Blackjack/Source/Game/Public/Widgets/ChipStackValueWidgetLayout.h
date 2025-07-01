#pragma once
#include <UISystem/WidgetLayout.h>

#include <UISystem/Widgets/ImageWidget.h>
#include <UISystem/Widgets/TextWidget.h>

class ChipStack;

class ChipStackValueWidgetLayout : public Core::WidgetLayout
{
public:
	ChipStackValueWidgetLayout(const String& inName) : Core::WidgetLayout(inName) {}
	virtual void Init() override;
	
	virtual void Tick(float deltaTime) override;

	void SetPosition(const glm::vec2& newPos);
	void SetValue(int32 value);
	void Enable(bool bEnable);

	void ProvideStacks(SharedPtr<ChipStack> chipStack);

public:
	WeakPtr<Core::ImageWidget> Background;
	WeakPtr<Core::TextWidget> Value;

	WeakPtr<ChipStack> PlayerStack;

};