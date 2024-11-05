#include "Core/TimerManager.h"
#include "Core/Application.h"

namespace Core
{

	TimerManager& TimerManager::Get()
	{
		TimerManager* singleton = Application::Get().m_TimerManager.get();
		BJ_ASSERT(singleton, "TimerManager doesn't exist!");
		return *singleton;
	}


}