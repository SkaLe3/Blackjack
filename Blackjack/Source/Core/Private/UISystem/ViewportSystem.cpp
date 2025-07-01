#include "UISystem/ViewportSystem.h"
#include "Core/Application.h"
#include "UISystem/ViewportClient.h"
#include "UISystem/Widget.h"

#include "Renderer/ScreenRenderer.h"

namespace Core
{

	ViewportSystem* ViewportSystem::s_Instance = nullptr;

	ViewportSystem& ViewportSystem::Get()
	{
		  return *s_Instance;
	}

	ViewportSystem::ViewportSystem()
	{
		s_Instance = this;
	}

	bool ViewportSystem::AddWidget(SharedPtr<Widget> widget, PanelSlot slot)
	{
		if (!widget)
		{
			BJ_LOG_INFO("Tried to add invalid widget");
			return false;
		}

		if (widget->GetParent())
		{
			BJ_LOG_INFO("Widget %s already has a parent. Can't be added to viewport", widget->GetName().c_str() );
			return false;
		}

		PanelSlot& slotInfo = m_ViewportWidgets[widget];
		widget->m_bManagedByViewportSystem = true;
		slotInfo = slot;

		std::shared_ptr<ViewportClient> vc = Application::GetViewportClient();
		vc->AddViewportWidgetContent(widget, slot.ZOrder);

		// TODO: broadcast
		return true;
	}

	void ViewportSystem::RemoveWidget(SharedPtr<Widget> widget)
	{
		if (widget)
		{
			m_ViewportWidgets.erase(widget);
		}
	}

	PanelSlot ViewportSystem::GetWidgetSlot(const SharedPtr<Widget> widget) const
	{
		if (widget && widget->m_bManagedByViewportSystem)
		{
			auto slot = m_ViewportWidgets.find(widget);
			if (slot != m_ViewportWidgets.end())
			{
				return slot->second;
			}
		}
		return PanelSlot();
	}

	glm::vec2 ViewportSystem::WorldToScreen(const glm::vec2& coords)
	{
		glm::mat4 worldViewProj = Application::Get().GetSceneRenderer()->GetViewProjection();
		glm::mat4 screenProj = Application::Get().GetScreenRenderer()->GetProjectionInverse();
		return screenProj * (worldViewProj * glm::vec4({coords, 0, 1}));
	}

	void ViewportSystem::AddViewportWidget(SharedPtr<Widget>, const int32 zOrder)
	{

	}

}