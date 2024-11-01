#pragma once
#include "Core/CoreDefines.h"
#include "World/World/Registry.h"

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
		void Render();

	public:
		template<typename T>
		SharedPtr<T> CreateComponent();

		template<typename T>
		SharedPtr<T> SpawnGameObject();

		template<typename T>
		void DestroyObject(WeakPtr<Object> object);
		void DestroyAll();

	private:
		Registry m_Registry;
		// TODO: GameMode
		uint32 m_ViewportWidth;
		uint32 m_ViewportHeight;
	
		bool m_bStarted = false;
	};

	template<typename T>
	SharedPtr<T> World::CreateComponent()
	{
		SharedPtr<T> component = MakeShared<T>();
		m_Registry.AddObject(component);
		if (m_bStarted)
			component->BeginPlay();
		return component;
	}

	template<typename T>
	SharedPtr<T> World::SpawnGameObject()
	{
		SharedPtr<T> object = MakeShared<T>();
		m_Registry.AddObject(object);
		if (m_bStarted)
			object->BeginPlay();
		return object;
	}

	template<typename T>
	void World::DestroyObject(WeakPtr<Object> object)
	{
		m_Registry.RemoveObject(object);
	}

}