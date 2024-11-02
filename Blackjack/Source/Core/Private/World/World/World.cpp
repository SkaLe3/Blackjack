#include "World/World/World.h"
#include "World/World/Registry.h"
#include "Renderer/Camera.h"
#include "World/Components/CameraComponent.h"
#include "Renderer/SceneRenderer.h"



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
		auto objects = m_Registry->GetAllObjects();
		for (auto object : objects)
		{
			object->BeginPlay();
		}
		m_bStarted = true;
	}

	void World::Tick(float deltaTime)
	{
		m_GameMode->Tick(deltaTime);
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
		   renderer->DrawSprite(object->GetTransformMatrix(), object->GetSprite());
	   }

	   renderer->EndScene();
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

	}

	void World::UseCamera(SharedPtr<CameraComponent> cc)
	{
	   	m_ActiveCamera = cc;
		m_ActiveCamera->GetCamera()->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	void World::DestroyObject(WeakPtr<Object> object)
	{
		m_Registry->SetPendingDestroy(object);
	}

}