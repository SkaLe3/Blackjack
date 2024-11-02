#pragma once

namespace Core
{
	template<typename T>
	SharedPtr<T> World::CreateComponent()
	{
		SharedPtr<T> component = MakeShared<T>();
		m_Registry->AddObject(component);
		if (m_bStarted)
			component->BeginPlay();
		return component;
	}

	template<typename T>
	SharedPtr<T> World::SpawnGameObject()
	{
		SharedPtr<T> object = MakeShared<T>();
		m_Registry->AddObject(object);
		if (m_bStarted)
			object->BeginPlay();
		return object;
	}
}