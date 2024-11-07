#pragma once
#include "Core/CoreDefines.h"

#ifdef BJ_DEBUG
	#define OBJECT_DEBUG_NAME() private: \
								const char* DebugGetClassName() { return typeid(*this).name();}
#else
	#define OBJECT_DEBUG_NAME()
#endif



namespace Core
{
	class World;

	class Object
	{
	public:
		virtual ~Object() = default;

		virtual void BeginPlay() = 0;
		virtual void Tick(float deltaTime) = 0;
		virtual void EndPlay() = 0;
		virtual void Destroy() = 0;

		SharedPtr<World> GetWorld();

		OBJECT_DEBUG_NAME()
	};
}