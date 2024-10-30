#pragma once
#include "Core/CoreDefines.h"
#include "World/Entities/GameObject.h"
#include "World/Components/GameComponent.h"
#include "World/Components/QuadComponent.h"
#include "World/Components/SpriteComponent.h"

#include <vector>


namespace Core
{
	class World
	{
	public:
		World() = default;
		virtual ~World() {}

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	public:
		template<typename T>
		SharedPtr<T> CreateComponent();
		{
			 SharedPtr<T> component = MakeShared<T>();
			 m_TickComponents.push_back(component);
			 if (m_bStarted)
				component->BeginPlay();
			return component;		 
		}

	private:
		std::vector<SharedPtr<GameComponent>> m_TickComponents;

		
		bool m_bStarted = false;
	};
}