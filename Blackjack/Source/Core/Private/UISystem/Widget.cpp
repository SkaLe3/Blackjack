#include "UISystem/Widget.h"
#include "UISystem/ViewportSystem.h"
#include "UISystem/PanelWidget.h"
#include "Renderer/ScreenRenderer.h"


namespace Core
{

	void Widget::OnPaint(SharedPtr<ScreenRenderer> renderer)
	{
#ifdef BJ_DEBUG
		if (m_bVisible)
		{
			AnchorData adata = GetParentRelatedAnchorData();
			glm::vec4 color = { 1.f, 0.f, 1.f, 0.3f };
			renderer->DrawWidget(adata.Position, adata.Size, adata.Alignment, color, false);
		}
#endif
	}

	AnchorData Widget::GetParentRelatedAnchorData()
	{
		if (Slot)
		{
			if (Slot->Parent)
			{
				AnchorData adata = Slot->Parent->GetParentRelatedAnchorData();
				AnchorData widgetData = Slot->LayoutData;
				widgetData.Position += adata.Position;
				return widgetData;
			}
			return Slot->LayoutData;

		}
		return AnchorData();
	}

	SharedPtr<PanelWidget> Widget::GetParent() const
	{
		if (Slot)
		{
			return Slot->Parent;
		}
		return nullptr;
	}

	void Widget::RemoveFromParent()
	{
		if (m_bManagedByViewportSystem)
		{
			ViewportSystem& vs = ViewportSystem::Get();
			vs.RemoveWidget(GetSelf());
		}
		else if (SharedPtr<PanelWidget> parent = GetParent())
		{
			parent->RemoveChild(GetSelf());
		}
	}

	void Widget::Tick(float deltaTime)
	{

	}

	bool Widget::OnMouseMoved(Event& event, const glm::vec2& mousePos)
	{
		ProvideMousePos(mousePos);
		return false;
	}

	bool Widget::OnButtonDown(Event& event, const glm::vec2& mousePos)
	{
		return false;
	}

	bool Widget::OnButtonUp(Event& event, const glm::vec2& mousePos)
	{
		return false;
	}

	bool Widget::ProvideMousePos(const glm::vec2& mousePos)
	{
		if (Slot)
		{
			AnchorData adata = Slot->LayoutData;
			const glm::vec2& pos = adata.Position;
			const glm::vec2& size = adata.Size;
			const glm::vec2& align = adata.Alignment;
			glm::vec2 corners[2] = { pos - size * align, pos + size * (1.0f - align) };

			if (mousePos.x > corners[0].x &&
				mousePos.x < corners[1].x &&
				mousePos.y > corners[0].y &&
				mousePos.y < corners[1].y)
			{
				m_bHovered = true;
				return m_bHovered;
			}
			m_bHovered = false;
			return m_bHovered;

		}
		m_bHovered = true;
		return m_bHovered;
	}

}