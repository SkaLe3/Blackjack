#pragma once
#include "World/Entities/GameObject.h"

namespace Core
{
	class SpriteComponent;

	class SpriteObject : public GameObject
	{
		DECLARE_SUPER(GameObject)
	public:
		SpriteObject();

		//~ Begin Object Interface
		virtual void Destroy() override;
		//~ End Object Interface

		SharedPtr<SpriteComponent> GetSpriteComponent() { return m_SpriteComponent.lock(); }

	private:
		WeakPtr<SpriteComponent> m_SpriteComponent;
	};
}