#include "World/World/Registry.h"

namespace Core
{

	void Registry::SetPendingDestroyAll()
	{
		auto allObject = GetAllObjects();
		for (auto& object : allObject)
		{
			m_PendingDestroyObjects.emplace_back(object);
		}
	}

	void Registry::RemoveDestroyed()
	{
		for (auto toDestroy : m_PendingDestroyObjects)
		{
			if (auto it = std::find(m_TickComponents.begin(), m_TickComponents.end(), toDestroy); it != m_TickComponents.end())
			{
				m_TickComponents.erase(it);
			}
			else if (auto it = std::find(m_TickGameObjects.begin(), m_TickGameObjects.end(), toDestroy); it != m_TickGameObjects.end())
			{
				m_TickGameObjects.erase(it);
			}
			else if (auto it = std::find(m_DrawableComponents.begin(), m_DrawableComponents.end(), toDestroy); it != m_DrawableComponents.end())
			{
				m_DrawableComponents.erase(it);
			}
		}
	}

	void Registry::ClearDestroyed()
	{
		m_PendingDestroyObjects.clear();
	}

	std::vector<SharedPtr<Object>> Registry::GetAllObjects()
	{
		std::vector<SharedPtr<Object>> ticks;
		ticks.reserve(m_TickComponents.size() + m_TickGameObjects.size() + m_DrawableComponents.size());
		ticks.insert(ticks.end(), m_TickComponents.begin(), m_TickComponents.end());
		ticks.insert(ticks.end(), m_TickGameObjects.begin(), m_TickGameObjects.end());
		ticks.insert(ticks.end(), m_DrawableComponents.begin(), m_DrawableComponents.end());
		return std::move(ticks);
	}

	std::vector<SharedPtr<SpriteComponent>>& Registry::GetAllDrawable()
	{
		return m_DrawableComponents;
	}

}