#include "World/World/World.h"
#include "World/World/Registry.h"
#include "Renderer/Camera.h"
#include "World/Components/CameraComponent.h"
#include "World/Entities/PlayerController.h"
#include "Renderer/SceneRenderer.h"
#include "Renderer/Sprite.h"



namespace Core
{

	World::World()
	{
		m_Registry = MakeUnique<Registry>();
		m_Renderer = SceneRenderer::Create();
	}

	void World::SetViewportSize(uint32 w, uint32 h)
	{
		m_ViewportWidth = w, m_ViewportHeight = h;
	}


	void World::BeginPlay()
	{
		m_GameMode->BeginPlay();
		if (m_PlayerController)
			m_PlayerController->BeginPlay();
		m_bStarted = true;
		auto objects = m_Registry->GetAllObjects();
		for (auto object : objects)
		{
			object->BeginPlay();
		}
		m_GameMode->PostBeginPlay();
		if (m_PlayerController)
			m_PlayerController->PostBeginPlay();
	}

	void World::Tick(float deltaTime)
	{
		m_GameMode->Tick(deltaTime);
		if (m_PlayerController)
			m_PlayerController->Tick(deltaTime);
		UpdateObjects(deltaTime);
		RemoveDestroyed();
		ClearDestroyed();

	}


	void World::Render()
	{
		CameraInfo info = m_ActiveCamera->GetCamera()->GetCameraInfo();
		info.ViewMatrix = glm::inverse(m_ActiveCamera->GetTransformMatrix());
		RenderScene(m_Renderer, info);
	}

	void World::RenderScene(const SharedPtr<SceneRenderer>& renderer, const CameraInfo& cameraInfo)
	{
		renderer->BeginScene(cameraInfo);

		auto drawable = m_Registry->GetAllDrawableSorted();
		for (SharedPtr<SpriteComponent>& object : drawable)
		{
			if (!object->GetSprite()->IsVisible()) continue;
			renderer->DrawSprite(object->GetTransformMatrix(), object->GetTransform().Scale, object->GetSprite());
		}
#if BJ_DEBUG_HELPERS
		auto ticks = m_Registry->GetTickComponents();
		for (SharedPtr<GameComponent>& object : ticks)
		{
			if (auto box = std::dynamic_pointer_cast<BoxComponent>(object); box && box->IsVisible())
			{
				renderer->DrawRect(box->GetTransformMatrix(), box->GetHalfSize(),  box->GetColor(), false);
			}
		}
#endif

		renderer->EndScene();
	}

	SharedPtr<Core::SceneRenderer> World::GetSceneRenderer()
	{
		return m_Renderer;
	}

	void World::DestroyAll()
	{
		m_Registry->SetPendingDestroyAll();
	}

	void World::UpdateObjects(float deltaTime)
	{
		auto objects = m_Registry->GetAllObjects();
		for (auto object : objects)
		{
			object->Tick(deltaTime);
		}
	}

	void World::RemoveDestroyed()
	{
		m_Registry->RemoveDestroyed();
	}

	void World::ClearDestroyed()
	{
		m_Registry->ClearDestroyed();
	}

	void World::ClearWorld()
	{
		m_ActiveCamera = nullptr;
		m_Registry = nullptr;
		m_GameMode = nullptr;
		m_PlayerController = nullptr;

	}

	void World::UseCamera(SharedPtr<CameraComponent> cc)
	{
		m_ActiveCamera = cc;
		m_ActiveCamera->GetCamera()->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	SharedPtr<GameMode> World::GetGameMode()
	{
		 return m_GameMode;
	}

	SharedPtr<PlayerController> World::GetPlayerController()
	{
		return m_PlayerController;
	}

	void World::DestroyObject(WeakPtr<Object> object)
	{
		m_Registry->SetPendingDestroy(object);
	}

}