#include "World/World/World.h"


namespace Core
{

	void World::BeginPlay()
	{
		m_GameMode->BeginPlay();
		auto objects = m_Registry.GetAllObjects();
		for (auto object : objects)
		{
			object->BeginPlay();
		}
		m_bStarted = true;
	}

	void World::Tick(float deltaTime)
	{
		m_GameMode->Tick(deltaTime);
		UpdateObjects(deltaTime);
		RemoveDestroyed();
		ClearDestroyed();

	}


	void World::DestroyAll()
	{
		m_Registry.SetPendingDestroyAll();
	}

	void World::UpdateObjects(float deltaTime)
	{
		auto objects = m_Registry.GetAllObjects();
		for (auto object : objects)
		{
			object->Tick(deltaTime);
		}
	}

	void World::RemoveDestroyed()
	{
		 m_Registry.RemoveDestroyed();
	}

	void World::ClearDestroyed()
	{
		m_Registry.ClearDestroyed();
	}

}