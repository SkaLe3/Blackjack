#include "World/World/Registry.h"

namespace Core
{

	void Registry::RemoveAll()
	{
		 auto allObject = GetAllTick();
		 for (auto& object : allObject)
		 {
			 m_PendingDestroyObjects.emplace_back(object);
		 }
		 m_TickComponents.clear();
		 m_TickGameObjects.clear();
		 m_DrawableComponents.clear();
	}

	std::vector<SharedPtr<Object>>&& Registry::GetAllTick()
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