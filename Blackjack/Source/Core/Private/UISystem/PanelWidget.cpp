#include "UISystem/PanelWidget.h"

#include "UISystem/PanelSlot.h"
#include "UISystem/WidgetLayout.h"

namespace Core
{

	void PanelWidget::Init()
	{
		Widget::Init();
		for (SharedPtr<PanelSlot> slot : m_Slots)
		{
			slot->Content->Init();
		}
	}

	void PanelWidget::Tick(float deltaTime)
	{
		for (auto& slot : m_Slots)
		{
			slot->Content->Tick(deltaTime);
		}
	}

	size_t PanelWidget::GetChildrenCount() const
	{
		return m_Slots.size();
	}

	int32 PanelWidget::GetChildIndex(const SharedPtr<Widget> content) const
	{
		if (content)
		{
			const int32 childCount = GetChildrenCount();
			for (int32 childIndex = 0; childIndex < childCount; childIndex++)
			{
				if (GetChildAt(childIndex) == content)
				{
					return childIndex;
				}
			}
		}
		return -1;
	}

	SharedPtr<Widget> PanelWidget::GetChildAt(int32 index) const
	{
		if (index < m_Slots.size() && index >= 0)
		{
			if (SharedPtr<PanelSlot> childSlot = m_Slots[index])
			{
				return childSlot->Content;
			}
		}
		return nullptr;
	}

	SharedPtr<PanelSlot> PanelWidget::AddChild(SharedPtr<Widget> content)
	{
		if (content == nullptr)
			return nullptr;
		content->RemoveFromParent();
		SharedPtr<PanelSlot> newSlot = MakeShared<PanelSlot>();
		newSlot->Content = content;
		newSlot->Parent = std::static_pointer_cast<PanelWidget>(GetSelf());
		content->Slot = newSlot;
		m_Slots.push_back(newSlot);
		return newSlot;
	}

	bool PanelWidget::RemoveChild(SharedPtr<Widget> content)
	{
		int32 childIndex = GetChildIndex(content);
		if (childIndex != -1)
		{
			return RemoveChildAt(childIndex);
		}
		return false;
	}

	bool PanelWidget::RemoveChildAt(size_t index)
	{
		if (index < 0 || index >= m_Slots.size())
			return false;

		SharedPtr<PanelSlot> panelSlot = m_Slots[index];
		m_Slots.erase(m_Slots.begin() + index);

		if (panelSlot)
		{
			if (panelSlot->Content)
			{
				panelSlot->Content->Slot = nullptr;
			}
			panelSlot->Parent = nullptr;
			panelSlot->Content = nullptr;
		}
		else
		{
			return false;
		}
		return true;
	}

	void PanelWidget::OnPaint(SharedPtr<ScreenRenderer> renderer)
	{
		std::sort(m_Slots.begin(), m_Slots.end(), [](const SharedPtr<PanelSlot>& a, const SharedPtr<PanelSlot>& b)
			{
				return a->GetZOrder() < b->GetZOrder();
			});
		for (auto& slot : m_Slots)
		{
			slot->Content->OnPaint(renderer);
		}
	}

	bool PanelWidget::OnMouseMoved(Event& event, const glm::vec2& mousePos)
	{
		ProvideMousePos(mousePos);
		for (auto& slot : m_Slots)
		{
			if (slot->Content)
			{
				if (slot->Content->IsVisible())
					slot->Content->OnMouseMoved(event, mousePos);
			}
		}
		return false;
	}

	bool PanelWidget::OnButtonDown(Event& event, const glm::vec2& mousePos)
	{
		if (m_bHovered)
		{
			bool handled = false;
			for (auto& slot : m_Slots)
			{
				if (slot->Content)
				{
					if (slot->Content->IsVisible())
						handled |= slot->Content->OnButtonDown(event, mousePos);
				}
				if (handled)
					break;
			}
			return handled;
		}
		return false;
	}

	bool PanelWidget::OnButtonUp(Event& event, const glm::vec2& mousePos)
	{
		if (m_bHovered)
		{
			bool handled = false;
			for (auto& slot : m_Slots)
			{
				if (slot->Content)
				{
					if (slot->Content->IsVisible())
						handled |= slot->Content->OnButtonUp(event, mousePos);
				}
				if (handled)
					break;
			}
			return handled;
		}
		return false;
	}

}