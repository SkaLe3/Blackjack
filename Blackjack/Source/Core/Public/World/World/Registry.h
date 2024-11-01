#pragma once
#include "Core/CoreDefines.h"
#include "World/Entities/GameObject.h"
#include "World/Components/GameComponent.h"
#include "World/Components/BoxComponent.h"
#include "World/Components/SpriteComponent.h"
#include <vector>
#include <type_traits>
#include <ranges>

namespace Core
{
	class Registry
	{
	public:
		template<typename T>
		void AddObject(SharedPtr<T> object);
		template<typename T>
		void SetPendingDestroy(WeakPtr<Object> object);
		void SetPendingDestroyAll();
		void RemoveDestroyed();
		void ClearDestroyed();

		std::vector<SharedPtr<Object>> GetAllObjects();
		std::vector<SharedPtr<SpriteComponent>>& GetAllDrawable();


	private:
		std::vector<SharedPtr<GameComponent>> m_TickComponents;
		std::vector<SharedPtr<SpriteComponent>> m_DrawableComponents;
		std::vector<SharedPtr<GameObject>> m_TickGameObjects;

		std::vector<SharedPtr<Object>> m_PendingDestroyObjects;

	};

	template<typename T>
	void Registry::AddObject(SharedPtr<T> object)
	{

		if constexpr (std::is_same<T, SpriteComponent>::value)
		{
			m_DrawableComponents.push_back(object);
		}
		else if constexpr (std::is_same<T, GameObject>::value)
		{
			m_TickGameObjects.push_back(object);
		}
		else
		{
			m_TickComponents.push_back(object);
		}
	}

	template<typename T>
	void Registry::SetPendingDestroy(WeakPtr<Object> object)
	{
		auto obj = object.lock();
		if constexpr (std::is_same<T, SpriteComponent>::value)
		{
			auto& v = m_DrawableComponents;
			
			if (auto it = std::find(v.begin(), v.end(), obj); it != v.end())
			{
			   m_PendingDestroyObjects.emplace_back(obj);
			}	

		}
		else if constexpr (std::is_same<T, GameObject>::value)
		{
			auto& v = m_TickGameObjects;

			if (auto it = std::find(v.begin(), v.end(), obj); it != v.end())
			{
				m_PendingDestroyObjects.emplace_back(obj);
			}
		}
		else
		{
			auto& v = m_TickComponents;

			if (auto it = std::find(v.begin(), v.end(), obj); it != v.end())
			{
				m_PendingDestroyObjects.emplace_back(obj);
			}
		}
	}

}