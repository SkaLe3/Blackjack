#pragma once
#include "Core/CoreDefines.h"
#include "World/Entities/GameMode.h"
#include "World/World/Registry.h"
#include "Renderer/SceneRenderer.h"
#include "Renderer/Camera.h"
#include "Layers/GameLayer.h"
#include "Core/Event.h"
#include <vector>


namespace Core
{
	class Registry;
	class CameraComponent;
	class PlayerController;
	
	class World
	{		  
	public:	
		template<typename T>
		static void OpenScene();
	public:
		World();
		virtual ~World() {}

		void SetViewportSize(uint32 w, uint32 h);

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void OnEvent(Event& event) = 0;
		void Render();
		void RenderScene(const SharedPtr<SceneRenderer>& renderer, const CameraInfo& cameraInfo);

	public:
		template<typename T>
		SharedPtr<T> CreateComponent();

		template<typename T>
		SharedPtr<T> SpawnGameObject();

		SharedPtr<GameMode> GetGameMode();
		SharedPtr<PlayerController> GetPlayerController();

		void DestroyObject(WeakPtr<Object> object);
		void DestroyAll();
		void UpdateObjects(float deltaTime);
		void RemoveDestroyed();
		void ClearDestroyed();

		void ClearWorld();


		void UseCamera(SharedPtr<CameraComponent> cc);

	protected:
		UniquePtr<Registry> m_Registry;
		SharedPtr<GameMode> m_GameMode;
		SharedPtr<PlayerController> m_PlayerController;
		SharedPtr<CameraComponent> m_ActiveCamera;

		SharedPtr<SceneRenderer> m_Renderer;

		uint32 m_ViewportWidth;
		uint32 m_ViewportHeight;

		bool m_bStarted = false;
	};

	template<typename T>
	void World::OpenScene()
	{
		 g_GameRef->OpenScene<T>();
	}

}
#include "World/World/World.inl"