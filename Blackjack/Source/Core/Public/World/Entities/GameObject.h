#pragma once
#include "Entities/Object.h"


namespace Core
{
	class GameObject : public Object, public std::enable_shared_from_this<GameObject>
	{
	public:
		//~ Begin Object Interface
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void EndPlay() override;
		virtual void Destroy() override;
		//~ End Object Interface

		inline WeakPtr<GameObject> GetSelf() { return weak_from_this(); }


	};
}