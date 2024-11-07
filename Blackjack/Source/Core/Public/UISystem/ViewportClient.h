#pragma once
#include "Core/CoreDefines.h"
#include "Core/Event.h"
#include "UISystem/PanelWidget.h"


#include <glm/glm.hpp>
#include <vector>

namespace Core
{
	class ScreenRenderer;
	class WidgetLayout;

	class ViewportClient
	{
	public:
		void Tick(double deltaTime);
		void AddViewportWidgetContent(SharedPtr<Widget> content, int32 zOrder);
		void RemoveViewportWidgetContent(SharedPtr<Widget> content);
		void RemoveAll();

		void Paint(SharedPtr<ScreenRenderer> renderer);

		bool OnMouseMoved(Event& event, const glm::vec2& mousePos);
		bool OnButtonDown(Event& event, const glm::vec2& mousePos);
		bool OnButtonUp(Event& event, const glm::vec2& mousePos);

		void Clear();

	private:
		void SortWidgets();

	private:
		std::vector<std::pair<SharedPtr<WidgetLayout>, int32>> m_ViewportOverlay;
	};

}
