#include "World/World/Registry.h"
#include "World/Entities/GameObject.h"

#include <algorithm>

namespace Core
{

	void Registry::SetPendingDestroy(WeakPtr<Object> object)
	{
		auto obj = object.lock();
		if (auto sprite = std::dynamic_pointer_cast<SpriteComponent>(obj); sprite)
		{
			auto& v = m_DrawableComponents;

			if (auto it = std::find(v.begin(), v.end(), sprite); it != v.end())
			{
				m_PendingDestroyObjects.emplace_back(obj);
			}

		}
		else if (auto gameObj = std::dynamic_pointer_cast<GameObject>(obj); gameObj)
		{
			auto& v = m_TickGameObjects;

			if (auto it = std::find(v.begin(), v.end(), gameObj); it != v.end())
			{
				m_PendingDestroyObjects.emplace_back(obj);
			}
		}
		else
		{
			auto& v = m_TickComponents;

			if (auto it = std::find(v.begin(), v.end(), std::static_pointer_cast<GameComponent>(obj)); it != v.end())
			{
				m_PendingDestroyObjects.emplace_back(obj);
			}
		}
	}

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
			if (auto it = std::find(m_TickComponents.begin(), m_TickComponents.end(), std::dynamic_pointer_cast<GameComponent>(toDestroy)); it != m_TickComponents.end())
			{
				m_TickComponents.erase(it);
			}
			else if (auto it = std::find(m_TickGameObjects.begin(), m_TickGameObjects.end(), std::dynamic_pointer_cast<GameObject>(toDestroy)); it != m_TickGameObjects.end())
			{
				m_TickGameObjects.erase(it);
			}
			else if (auto it = std::find(m_DrawableComponents.begin(), m_DrawableComponents.end(), std::dynamic_pointer_cast<SpriteComponent>(toDestroy)); it != m_DrawableComponents.end())
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
		return ticks;
	}

	std::vector<SharedPtr<SpriteComponent>>& Registry::GetAllDrawable()
	{
		return m_DrawableComponents;
	}

	std::vector<SharedPtr<SpriteComponent>>& Registry::GetAllDrawableSorted()
	{
		std::sort(m_DrawableComponents.begin(), m_DrawableComponents.end(),
				  [](SharedPtr<SpriteComponent>& s1, SharedPtr<SpriteComponent>& s2)
				  {
					  return s1->GetWorldTransform().Translation.z < s2->GetWorldTransform().Translation.z;
				  });
		return m_DrawableComponents;
	}
#ifdef BJ_DEBUG
	std::vector<SharedPtr<Core::GameComponent>>& Registry::GetTickComponents()
	{
		return m_TickComponents;
	}
#endif

}