#pragma once
#include "Core/CoreDefines.h"
#include "UISystem/PanelSlot.h"

#include <unordered_map>

namespace Core
{
	class Widget;
	
	class ViewportSystem
	{
	public:
		static ViewportSystem& Get();

	public:
		ViewportSystem();

		bool AddWidget(SharedPtr<Widget> widget, PanelSlot slot);
		void RemoveWidget(SharedPtr<Widget> widget);
		PanelSlot GetWidgetSlot(const SharedPtr<Widget> widget) const;

		glm::vec2 WorldToScreen(const glm::vec2& coords);
	private:
		void AddViewportWidget(SharedPtr<Widget>, const int32 zOrder);

	private:
		using ViewportWidgetList = std::unordered_map<SharedPtr<Widget>, PanelSlot>;
		ViewportWidgetList m_ViewportWidgets;

	private:
		static ViewportSystem *s_Instance;
	};
}