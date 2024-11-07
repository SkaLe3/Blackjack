#pragma once
#include "UISystem/Widget.h"

#include <vector>

namespace Core
{
	class PanelSlot;

	class PanelWidget : public Widget
	{
	public:
		PanelWidget(const String& inName) : Widget(inName) {}
		size_t GetChildrenCount() const;
		int32 GetChildIndex(const SharedPtr<Widget> content) const;
		SharedPtr<Widget> GetChildAt(int32 index) const;
		SharedPtr<PanelSlot> AddChild(SharedPtr<Widget> content);
		bool RemoveChild(SharedPtr<Widget> content);
		bool RemoveChildAt(size_t index);

		virtual void OnPaint(SharedPtr<ScreenRenderer> renderer) override;


		virtual bool OnMouseMoved(Event& event, const glm::vec2& mousePos) override;
		virtual bool OnButtonDown(Event& event, const glm::vec2& mousePos)override;
		virtual bool OnButtonUp(Event& event, const glm::vec2& mousePos)override;

	protected:
		std::vector<SharedPtr<PanelSlot>> m_Slots;

	};
}