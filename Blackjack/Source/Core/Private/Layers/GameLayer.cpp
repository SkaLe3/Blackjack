#include "Layers/GameLayer.h"

#include "Core/AssetManager.h"
#include "World/World/World.h"

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

	void GameLayer::OnAttach()
	{
		SetWorld(m_StartingSceneFN());
		m_CurrentWorld->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		m_CurrentWorld->BeginPlay();
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
			m_CurrentWorld->ClearWorld();
			SetWorld(m_NextWorld);
			m_CurrentWorld->BeginPlay();
			m_bSwtichWorld = false;
			AssetManager::Get().ClearCache();
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

	bool GameLayer::OnKeyPressed(Event& event)
	{
// 		if (event.Ev.key.keysym.sym == SDLK_SPACE)
// 		{
// 			startAnim = true;
// 			SharedPtr<SoundBase> sound = AssetManager::Get().Load<SoundAsset>("S_Yipee")->SoundP;
// 			SharedPtr<SoundBase> music = AssetManager::Get().Load<SoundAsset>("S_Music1")->SoundP;
// 			AudioSystem::PlaySound(sound);
// 		}
// 		if (event.Ev.key.keysym.sym == SDLK_r)
// 		{
// 			AudioSystem::StopAllSounds();
// 			SharedPtr<SoundBase> sound = AssetManager::Get().Load<SoundAsset>("S_Music1")->SoundP;
// 			AudioSystem::PlayMusic(sound);
// 
// 		}
// 		if (event.Ev.key.keysym.sym == SDLK_EQUALS)
// 		{
// 			//AudioSystem::SetMasterVolume(1.0f); 
// 			AudioSystem::SetMusicVolume(1.0f);
// 			AudioSystem::SetSFXVolume(1.0f);
// 		}
// 		if (event.Ev.key.keysym.sym == SDLK_MINUS)
// 		{
// 			AudioSystem::SetMusicVolume(0.1f);
// 			AudioSystem::SetSFXVolume(0.1f);
// 			//AudioSystem::SetMasterVolume(0.1f);
// 		}
		return true;
	}

}