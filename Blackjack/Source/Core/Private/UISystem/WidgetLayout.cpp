#include "UISystem/WidgetLayout.h"
#include "UISystem/ViewportSystem.h"
#include "UISystem/PanelWidget.h"

namespace Core
{

	void WidgetLayout::Init()
	{

	}

	void WidgetLayout::AddToViewport(int32 zOrder /*= 0*/)
	{
		ViewportSystem& vs = ViewportSystem::Get();
		PanelSlot slot;
		if (m_bManagedByViewportSystem)
		{
			slot = vs.GetWidgetSlot(GetSelf());
		}
		slot.ZOrder = zOrder;
		vs.AddWidget(GetSelf(), slot);
	}

	void WidgetLayout::RemoveFromViewport()
	{
		ViewportSystem& vs = ViewportSystem::Get();
		if (m_bManagedByViewportSystem)
		{
			vs.RemoveWidget(GetSelf());
		}
		else if (SharedPtr<PanelWidget> parent = GetParent())
		{
			parent->RemoveChild(GetSelf());
		}
	}

	void WidgetLayout::SetRootWidget(SharedPtr<PanelWidget> inRootWidget)
	{
		RootWidget = inRootWidget;
	}

	void WidgetLayout::OnPaint(SharedPtr<ScreenRenderer> renderer)
	{
		RootWidget->OnPaint(renderer);
	}

	bool WidgetLayout::OnMouseMoved(Event& event, const glm::vec2& mousePos)
	{
		return RootWidget->OnMouseMoved(event, mousePos);
	}

	bool WidgetLayout::OnButtonDown(Event& event, const glm::vec2& mousePos)
	{
		return RootWidget->OnButtonDown(event, mousePos);
	}

	bool WidgetLayout::OnButtonUp(Event& event, const glm::vec2& mousePos)
	{
		return RootWidget->OnButtonUp(event, mousePos);
	}

}