#pragma once
#include "Core/CoreDefines.h"
//#include "World/Entities/GameObject.h"
#include "World/Components/GameComponent.h"
#include "World/Components/BoxComponent.h"
#include "World/Components/SpriteComponent.h"
#include <vector>
#include <type_traits>

namespace Core
{
	class GameObject;

	class Registry
	{
	public:
		template<typename T>
		void AddObject(SharedPtr<T> object);
		void SetPendingDestroy(WeakPtr<Object> object);
		void SetPendingDestroyAll();
		void RemoveDestroyed();
		void ClearDestroyed();

		std::vector<SharedPtr<Object>> GetAllObjects();
		std::vector<SharedPtr<SpriteComponent>>& GetAllDrawable();
		std::vector<SharedPtr<SpriteComponent>>& GetAllDrawableSorted();


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
		else if constexpr (std::is_base_of<GameObject, T>::value)
		{
			m_TickGameObjects.push_back(object);
		}
		else
		{
			m_TickComponents.push_back(object);
		}
	}



}