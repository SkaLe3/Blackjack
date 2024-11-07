#include "World/Entities/PlayerController.h"


namespace Core
{

	void PlayerController::Posses(SharedPtr<GameObject> player)
	{
		m_PossesedObject = player;
	}

}