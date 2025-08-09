#include "UISystem/ViewportClient.h"
#include "Renderer/ScreenRenderer.h"

#include "UISystem/WidgetLayout.h"
#include <algorithm>

namespace Core
{

	void ViewportClient::Tick(double deltaTime)
	{
		for (auto& [widget, zOrder] : m_ViewportOverlay)
		{
			widget->Tick(deltaTime);
		}
	}

	void ViewportClient::AddViewportWidgetContent(SharedPtr<Widget> content, int32 zOrder)
	{
		SharedPtr< WidgetLayout> widget = std::static_pointer_cast<WidgetLayout>(content);
		m_ViewportOverlay.emplace_back(std::make_pair(widget, zOrder));
	}

	void ViewportClient::RemoveViewportWidgetContent(SharedPtr<Widget> content)
	{
		SharedPtr< WidgetLayout> widget = std::static_pointer_cast<WidgetLayout>(content);
		m_ViewportOverlay.erase(
			std::remove_if(m_ViewportOverlay.begin(), m_ViewportOverlay.end(),
				[&widget](const auto& elem)
				{
					return elem.first == widget;
				}), m_ViewportOverlay.end()
					);
	}

	void ViewportClient::RemoveAll()
	{
		m_ViewportOverlay.clear();
	}


	void ViewportClient::Paint(SharedPtr<ScreenRenderer> renderer)
	{
		SortWidgets();
		for (auto& [widget, zOrder] : m_ViewportOverlay)
		{
			if (widget->IsVisible())
			{
				widget->OnPaint(renderer);
			}
		}
	}

	bool ViewportClient::OnMouseMoved(Event& event, const glm::vec2& mousePos)
	{
		for (auto it = m_ViewportOverlay.rbegin(); it != m_ViewportOverlay.rend(); ++it)
		{
			auto& [widget, zOrder] = (*it);
			if (widget->IsVisible())
				widget->OnMouseMoved(event, mousePos);
		}
		return false;
	}

	bool ViewportClient::OnButtonDown(Event& event, const glm::vec2& mousePos)
	{
		bool handled = false;
		for (auto it = m_ViewportOverlay.rbegin(); it != m_ViewportOverlay.rend(); ++it)
		{
			auto& [widget, zOrder] = (*it);
			handled |= widget->OnButtonDown(event, mousePos);
			if (handled)
				return true;
		}
		return false;
	}


	bool ViewportClient::OnButtonUp(Event& event, const glm::vec2& mousePos)
	{
		bool handled = false;
		for (auto it = m_ViewportOverlay.rbegin(); it != m_ViewportOverlay.rend(); ++it)
		{
			auto& [widget, zOrder] = (*it);
			handled |= widget->OnButtonUp(event, mousePos);
			if (handled)
				return true;
		}
		return false;
	}

	void ViewportClient::Clear()
	{
		for (auto& [widget, zOrder] : m_ViewportOverlay)
		{
			widget->RemoveFromViewport();
		}
		m_ViewportOverlay.clear();
	}

	void ViewportClient::SortWidgets()
	{
		std::sort(m_ViewportOverlay.begin(), m_ViewportOverlay.end(),
			[](const std::pair<SharedPtr<WidgetLayout>, int32>& a, const std::pair<SharedPtr<WidgetLayout>, int32>& b)
			{
				return a.second < b.second;
			});
	}

}