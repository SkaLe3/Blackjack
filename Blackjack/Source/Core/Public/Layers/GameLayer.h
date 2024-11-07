#pragma once
#include "Core/CoreDefines.h"
#include "Core/Event.h"

#include "Layers/Layer.h"


// TEMPORARY
#include <SDL2/SDL.h>
#include <Renderer/Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Core
{
	class World;

	class GameLayer : public Layer
	{
	public:
		GameLayer(std::function<SharedPtr<World>()> startingSceneFunc, uint32 viewportWidth, uint32 viewportHeight);

		void Init() override;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(float deltaTime) override;
		void OnEvent(Event& event) override;

		void SetWorld(SharedPtr<World> world);
		SharedPtr<World> GetWorld();

		template<typename T>
		void OpenScene();
	private:
		template<typename T>
		SharedPtr<World> CreateScene();

		// TEMPORARY
		bool OnKeyPressed(Event& event);

	private:
		SharedPtr<World> m_CurrentWorld;
		SharedPtr<World> m_NextWorld;
		bool m_bSwtichWorld = false;
		std::function<SharedPtr<World>()> m_StartingSceneFN;

		uint32 m_ViewportWidth, m_ViewportHeight;

	private:

	};

	extern GameLayer* g_GameRef;

	template<typename T>
	void GameLayer::OpenScene()
	{
		m_NextWorld = CreateScene<T>();
		m_bSwtichWorld = true;
	}

	template<typename T>
	SharedPtr<World> GameLayer::CreateScene()
	{
		return MakeShared<T>();
	}

}