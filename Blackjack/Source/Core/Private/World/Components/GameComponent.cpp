#include "World/Components/GameComponent.h"
#include "World/World/World.h"

namespace Core
{

	void GameComponent::Destroy()
	{
		GetWorld()->DestroyObject(GetSelf());
	}
}