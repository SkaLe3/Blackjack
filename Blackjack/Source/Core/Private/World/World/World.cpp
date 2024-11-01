#include "World/World/World.h"


namespace Core
{

	void World::Tick(float deltaTime)
	{

	}


	void World::DestroyAll()
	{
		m_Registry.RemoveAll();
	}

}