#pragma once
#include "UISystem/Widget.h"


namespace Core
{
	class WidgetLayout : public Widget
	{
	public:
		WidgetLayout(const String& inName) : Widget(inName) {}

		virtual void Init() override;
		virtual void Tick(float deltaTime) override;


		void AddToViewport(int32 zOrder = 0);
		void RemoveFromViewport();

		void SetRootWidget(SharedPtr<PanelWidget> inRootWidget);

		virtual void OnPaint(SharedPtr<ScreenRenderer> renderer) override;

		virtual bool OnMouseMoved(Event& event, const glm::vec2& mousePos) override;
		virtual bool OnButtonDown(Event& event, const glm::vec2& mousePos) override;
		virtual bool OnButtonUp(Event& event, const glm::vec2& mousePos) override;

	public:
		SharedPtr<PanelWidget> RootWidget;
	};

	template<typename TWidgetL>
	SharedPtr<TWidgetL> CreateWidgetLayout(const String& widgetName)
	{
		return MakeShared<TWidgetL>(widgetName);
	}
}