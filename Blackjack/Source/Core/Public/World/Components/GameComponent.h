#pragma once
#include "World/Entities/Object.h"

namespace Core
{
	class GameObject;

	class GameComponent : public Object, public std::enable_shared_from_this<GameComponent>
	{
	public:
		void SetOwner(WeakPtr<GameObject> object) { m_Owner = object; }
		void RemoveOwner() { m_Owner.reset(); }
		inline WeakPtr<GameObject> GetOwner() { return m_Owner; }
		WeakPtr<GameComponent> GetSelf() { return weak_from_this(); }

	protected:
		WeakPtr<GameObject> m_Owner;
	};
}