#include "World/Entities/Object.h"
#include "Layers/GameLayer.h"
#include "World/World/World.h"

namespace Core
{



	SharedPtr<World> Object::GetWorld()
	{
		return g_GameRef->GetWorld();
	}

}