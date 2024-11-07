#pragma once
#include "Core/CoreDefines.h"
#include "World/Entities/Object.h"


namespace Core
{

	class GameMode : public Object
	{
	public:
		//~ Begin Object Interface
		virtual void BeginPlay() override {};
		virtual void Tick(float deltaTime) override {}
		virtual void EndPlay() override {}
		virtual void Destroy() override {}
		//~ Eng Object Interface

		void LeaveGame();
	};
}