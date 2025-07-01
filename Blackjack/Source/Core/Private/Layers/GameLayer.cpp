#include "Layers/GameLayer.h"

#include "Core/AssetManager.h"
#include "World/World/World.h"
#include "Core/Application.h"
#include "UISystem/ViewportClient.h"

// TEMPORARY
#include "Renderer/Renderer.h"
#include "Sound/AudioSystem.h"

namespace Core
{
	GameLayer* g_GameRef = nullptr;


	GameLayer::GameLayer(std::function<SharedPtr<World>()> startingSceneFunc, uint32 viewportWidth, uint32 viewportHeight)
		: m_StartingSceneFN(startingSceneFunc), m_ViewportWidth(viewportWidth), m_ViewportHeight(viewportHeight)
	{
		g_GameRef = this;
	}

	void GameLayer::Init()
	{
		SetWorld(m_StartingSceneFN());
		m_CurrentWorld->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		m_CurrentWorld->BeginPlay();
	}

	void GameLayer::OnAttach()
	{

	}

	void GameLayer::OnDetach()
	{

	}

	void GameLayer::OnUpdate(float deltaTime)
	{
		m_CurrentWorld->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		m_CurrentWorld->Tick(deltaTime);
		m_CurrentWorld->Render();
		if (m_bSwtichWorld)
		{
			Application::GetViewportClient()->Clear();
			AssetManager::Get().ClearCache();
			m_CurrentWorld->ClearWorld();
			SetWorld(m_NextWorld);
			m_CurrentWorld->BeginPlay();
			m_bSwtichWorld = false;
		}
	}

	void GameLayer::OnEvent(Event& event)
	{
		EventDispatcher disp(event);
		disp.Dispatch(SDL_KEYDOWN, BJ_BIND_EVENT_FN(GameLayer::OnKeyPressed));

		m_CurrentWorld->OnEvent(event);
	}

	void GameLayer::SetWorld(SharedPtr<World> world)
	{
		m_CurrentWorld = world;
		m_CurrentWorld->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	SharedPtr<World> GameLayer::GetWorld()
	{
	   return m_CurrentWorld;
	}

	SharedPtr<Core::SceneRenderer> GameLayer::GetSceneRenderer()
	{
		return m_CurrentWorld->GetSceneRenderer();
	}

	bool GameLayer::OnKeyPressed(Event& event)
	{
		return true;
	}

}