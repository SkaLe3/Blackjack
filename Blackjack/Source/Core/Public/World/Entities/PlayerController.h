#pragma once
#include <World/Entities/GameObject.h>


namespace Core
{
	class PlayerController : public GameObject
	{
		DECLARE_SUPER(GameObject)
	public:
		virtual void PostBeginPlay() {};
		void Posses(SharedPtr<GameObject> player);

	private:
		SharedPtr<GameObject> m_PossesedObject;
	};
}